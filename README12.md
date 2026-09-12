# My Part (Member 5) — Schema Analyzer, AI Schema Mapping & Connector Generator

## 1. What is the overall project?

This is a **government interoperability platform** prototype. The problem it solves: different government departments (Identity, Revenue, Education, etc.) each store citizen data in their own legacy formats and field names (e.g. `CITZ_NO`, `stud_no`, `INC_AMT`). To let departments talk to each other, every department's data needs to be automatically mapped onto one **canonical citizen schema**, and a **connector** (a small config describing how to talk to that department's system) needs to be generated so a central system can actually integrate with it.

The team split the work into a pipeline of steps, and **each team member owns a step or a contract (data shape)** so everyone could build in parallel without waiting on each other. That's why you'll see "Contract A / B / C" and "frozen on Day 1" comments everywhere in the code — they're the interfaces the team agreed on up front.

**My role (Member 5) covers three of these steps, split into two microservices:**

| Service | Port | Endpoints | Steps owned |
|---|---|---|---|
| `schema-mapper` | 8001 | `POST /analyze-schema`, `POST /map-schema` | Step 2 (Schema Analyzer), Step 3 (AI Schema Mapping) |
| `connector-generator` | 8002 | `POST /generate-connector` | Step 4 (Connector Configuration Generator) |

## 2. The full pipeline (so you can answer "where does your part fit?")

1. **Step 1 — Raw department data.** A department submits a sample of its data (JSON or XML). This uses the **canonical citizen model (Contract A)**, which Member 4 owns/defines: `citizenId, fullName, dateOfBirth, annualIncome, course`.
2. **Step 2 — Schema Analyzer (mine).** Takes that raw sample and extracts a flat `field_name -> type` map (string/number/date/boolean). No AI involved — pure parsing logic.
3. **Step 3 — AI Schema Mapping (mine).** Takes the extracted source fields + the canonical schema for the relevant service, sends both to **Gemini**, and asks it to propose which source field maps to which canonical field, with a confidence score and reasoning. Output must match **Contract B** exactly (`MappingResponse`), because Member 6 validates against that shape.
4. **Human approval (Member 6).** A human reviews the AI-proposed mappings and approves/edits them. This is the safety gate before anything becomes a live connector.
5. **Step 4 — Connector Configuration Generator (mine).** Takes *only the approved mappings* (never raw AI output) plus protocol/endpoint info, and assembles the final **Connector Configuration (Contract C)** — deterministically, with **no LLM call**.
6. **Downstream — Member 4's service consumes Contract C** to actually stand up/run the integration with that department.

**Why this matters if cross-questioned "why is step 4 separate from step 3 if they're both yours?"** — Step 3 is AI-driven and probabilistic (needs human review before anything is trusted). Step 4 is deterministic assembly that must happen *after* a human has approved the mappings — mixing them into one step would mean an unapproved, possibly-hallucinated mapping could become a live connector. Splitting them enforces a **human-in-the-loop safety gate** by architecture, not just by convention.

## 3. Tech stack used, and why

| Technology | Where used | Why this choice |
|---|---|---|
| **Python 3.13** | Everything | Fast to prototype, huge ecosystem for both web APIs and AI SDKs |
| **FastAPI** | Both services (`main.py`) | Modern async Python web framework; auto-generates OpenAPI docs; integrates natively with Pydantic for request/response validation, which is exactly what's needed to enforce the frozen "contracts" |
| **Uvicorn** | ASGI server to run FastAPI apps | Standard lightweight ASGI server recommended for FastAPI |
| **Pydantic** | `models.py` in both services | Enforces the exact shape of Contracts A/B/C at runtime — if a request doesn't match, FastAPI auto-returns a 422 error. This is critical in a multi-person project where everyone depends on exact field names/types |
| **google-genai SDK** (`from google import genai`) | `ai_mapper.py` | Official Python SDK to call Google's Gemini models |
| **Gemini (`gemini-3.5-flash-lite`)** | `ai_mapper.py` | A lightweight/fast Gemini model — chosen because schema mapping is a short classification-style task (compare two small field lists), not long-form generation, so a "flash-lite" model is fast and cheap while being sufficient for the reasoning needed |
| **python-dotenv** | `ai_mapper.py` (`load_dotenv()`) | Loads `GEMINI_API_KEY` from a `.env` file instead of hardcoding it in source — keeps secrets out of the codebase |
| **Python stdlib `json` / `xml.etree.ElementTree`** | `schema_analyzer.py` | No need for a heavy parsing library for a flat JSON object or simple flat XML — stdlib is sufficient and has zero extra dependencies |

## 4. Detailed, line-by-line walkthrough of every file

### 4.1 `schema-mapper/models.py` — the contracts

This file defines every data shape my service touches, and explicitly marks which are "frozen" team contracts vs. internal-only:

- `FieldType = Literal["string","number","date","boolean"]` — the only four types allowed anywhere in the system. Using `Literal` means Pydantic will *reject* any other value automatically.
- **Contract A — `CanonicalCitizenModel`**: owned by Member 4, I only *consume* this shape (`citizenId, fullName, dateOfBirth, annualIncome, course`).
- **Contract B — `Mapping` / `MappingResponse`**: this is *my* service's output, and Member 6 depends on it. `Mapping` has `source, sourceType, target, targetType, confidence (0–1, enforced by `Field(ge=0, le=1)`), reason`. `MappingResponse` wraps a list of these plus `mappingId, departmentId, serviceId`.
- **Internal-only models** (`SchemaAnalyzeRequest/Response`, `MapSchemaRequest`): these aren't shared contracts, so I was free to design them however was convenient — e.g. `fields: dict[str, str]` for a flat field→type map.

**Why `Optional[dict]` for `canonical_fields` in `MapSchemaRequest`?** So a caller can either pass a custom canonical schema, or omit it and let the service look it up by `serviceId` from a built-in table (see 4.3 below) — flexibility for testing vs. production use.

### 4.2 `schema-mapper/schema_analyzer.py` — Step 2, no AI

**Purpose:** turn a raw JSON or XML sample into a flat `{field_name: type}` map. Deliberately simple — the project docs say "For the prototype, JSON/XML is sufficient" and OpenAPI/Swagger parsing was explicitly optional/skipped.

- `_infer_type(value)`: checks Python type — `bool` first (important: in Python, `bool` is a subclass of `int`, so booleans must be checked *before* numbers or `True` would be misclassified as a number), then `int`/`float` → `"number"`, then `str` → date-or-string via the heuristic below, else defaults to `"string"`.
- `_looks_like_date(value)`: a **heuristic**, not a real date parser — a string counts as a date if it has ≥6 digits and ≥2 separator characters (`-` or `/`). Good enough for demo values like `"2004-04-12"` or `"12/04/2004"`. *(Weak point to be upfront about: a date with no separators, like `"20040412"`, would be misclassified as a plain string. This is a known, accepted limitation for a prototype.)*
- `analyze_json_sample`: `json.loads()` the string, require it to be a flat `dict` (raises `ValueError` otherwise — nested JSON is explicitly out of scope), then map every key through `_infer_type`.
- `analyze_xml_sample`: parses with `ElementTree`, iterates direct children of the root, and classifies each child's text using a slightly different (cruder) number check (`text.replace(".", "", 1).isdigit()`) plus the same date heuristic. Also flat-only — nested XML elements/attributes are not handled.
- `analyze_schema(fmt, sample)`: the single public entry point — dispatches to the JSON or XML function based on `fmt`, raises `ValueError` for anything else.

**Verified example (from the actual sample files in the project):**
- `identity_sample.json` → `{"citizenId": "string", "name": "string", "dateOfBirth": "date"}`
- `education_sample.json` → `{"stud_no": "string", "stud_name": "string", "course_cd": "string"}`
- `revenue_sample.xml` → `{"CITZ_NO": "string", "INC_AMT": "number", "DOB_VAL": "date"}`

### 4.3 `schema-mapper/ai_mapper.py` — Step 3, the AI part

This is the most "interesting" file to be cross-questioned on. Walkthrough:

1. **Setup:** `load_dotenv()` reads `.env`, then `client = genai.Client(api_key=os.environ.get("GEMINI_API_KEY"))` creates the Gemini client once at import time (not per-request — avoids re-creating the client on every call).
2. **`CANONICAL_FIELDS_DEFAULT`**: the full canonical schema (all 5 fields), used as a fallback reference.
3. **`SERVICE_CANONICAL_FIELDS`**: a hardcoded dict keyed by `serviceId` (`IDENTITY_VERIFICATION`, `REVENUE_VERIFICATION`, `EDUCATION_VERIFICATION`) — each service only needs a *subset* of canonical fields relevant to it. *(Cross-question: "what if a new service is added?" — Answer honestly: right now it requires a code change to this dict; in a production version this would live in a database/config file instead of hardcoded Python.)*
4. **`SYSTEM_PROMPT`**: this is the actual prompt engineering. Key rules I baked in:
   - Only map when there's a genuine semantic match (rule 1–2), with worked examples like `CITZ_NO → citizenId`, `INC_AMT → annualIncome`.
   - **Never invent source or target fields** (rules 4–5) — this matters because it's the first line of defense against hallucination.
   - Confidence must be 0–1 with a short reason (rules 7–8).
   - **Must respond with ONLY valid JSON** in an exact structure — this makes the response machine-parseable without needing a more complex structured-output API.
5. **`map_schema(...)` function — the core logic:**
   - Resolves the canonical schema: explicit `canonical_fields` param if given, else lookup via `SERVICE_CANONICAL_FIELDS[service_id]`; raises `ValueError` if the service is unknown.
   - Builds a `user_prompt` string that lists the source fields and canonical fields as JSON.
   - Calls `client.models.generate_content(model="gemini-3.5-flash-lite", contents=...)`.
   - **Defensive parsing:** strips ```` ```json ```` / ```` ``` ```` fences in case the model adds markdown formatting despite being told not to (a very common real-world LLM quirk).
   - Parses the JSON; if it fails, raises a clear `ValueError` including the raw text (helps debugging instead of a cryptic crash).
   - **This is the most important part for "why is this safe to use with an LLM" questions — validation of every single field returned by the model, never trusted blindly:**
     - `if source not in source_fields: continue` → drops any field the LLM invented that wasn't actually in the input (**prevents hallucinated source fields**).
     - `if target not in canonical: continue` → drops any invented canonical target (**prevents hallucinated target fields**).
     - **Types are taken from *our* schemas, not from what the LLM says** (`source_type = source_fields[source]`, not from the LLM's JSON) — so even if the LLM guesses a wrong type, the final output is always correct because it's overwritten with ground truth.
     - Extra guard confirming both types are in the allowed set of four.
     - `confidence` is coerced to `float`, defaulting to `0.0` on failure, then clamped to `[0, 1]` with `max(0.0, min(1.0, confidence))` — protects against the LLM returning a string, a negative number, or something >1.
     - `reason` has a sensible default string if the LLM omits it.
   - Finally constructs and returns a `MappingResponse` (Contract B) — guaranteed to match the shape Member 6 expects, **regardless of what the raw LLM output actually contained.**

**Worked example, end-to-end (Revenue department), to say out loud in your presentation:**
Input source fields (from Step 2, on `revenue_sample.xml`): `{"CITZ_NO": "string", "INC_AMT": "number", "DOB_VAL": "date"}`. Canonical for `REVENUE_VERIFICATION`: `{"citizenId": "string", "annualIncome": "number", "dateOfBirth": "date"}`. The AI mapper would be expected to return three mappings: `CITZ_NO → citizenId`, `INC_AMT → annualIncome`, `DOB_VAL → dateOfBirth`, each with high confidence and a short reason (these exact examples are even given to the model in the system prompt, so this case is close to guaranteed to work correctly).

### 4.4 `schema-mapper/main.py` — wiring it together

- Creates the FastAPI app.
- `POST /analyze-schema` → calls `analyze_schema()`, catches `(ValueError, Exception)` and returns HTTP 400 with the error message. *(Minor code-review note if asked: catching `Exception` after `ValueError` is redundant since `Exception` already covers `ValueError` — a small cleanup opportunity, not a bug.)*
- `POST /map-schema` → calls `map_schema()` directly (no try/except here — an uncaught `ValueError`, e.g. unknown `serviceId`, would currently surface as a generic 500 rather than a clean 400; another honest improvement point).
- `GET /health` → simple liveness check, standard practice for services that will run behind a load balancer/orchestrator.

### 4.5 `connector-generator/models.py` — Contract C

- `MappingPair`: a stripped-down `source/target` pair (no type/confidence/reason needed anymore — those were only relevant during the AI proposal + approval stage).
- `ConnectorConfig` (**Contract C**, frozen, Member 4 consumes this exact shape): `departmentId, departmentName (optional), protocol (REST/XML/SOAP only, via Literal), endpoint, mappings`.
- `GenerateConnectorRequest`: same fields, but with `approved_mappings` instead of `mappings` — the naming is intentional, to make it explicit in the type itself that only *already-approved* mappings should ever reach this service.

### 4.6 `connector-generator/generator.py` — Step 4, deterministic, no LLM

This is short by design, and that's the point to emphasize if asked "why is this file so simple?":

```python
def generate_connector_config(req: GenerateConnectorRequest) -> ConnectorConfig:
    if not req.approved_mappings:
        raise ValueError("Cannot generate a connector with zero approved mappings")
    return ConnectorConfig(
        departmentId=req.departmentId,
        departmentName=req.departmentName,
        protocol=req.protocol,
        endpoint=req.endpoint,
        mappings=[MappingPair(source=m.source, target=m.target) for m in req.approved_mappings],
    )
```

- One guard clause: refuse to generate a connector with zero approved mappings (a connector that maps nothing is useless and almost certainly a bug upstream).
- Otherwise, it's a pure, deterministic re-shaping of the input into Contract C — **no LLM, no network call, no randomness.** The docstring explicitly says not to ask an LLM to generate a full service here — only to assemble the structured config from mappings a human has already approved.

**Why this design choice matters (likely cross-question): "Couldn't you just have the LLM generate the connector directly in one step?"**
Answer: No — that would remove the human-approval checkpoint and make the final, *deployed* integration dependent on an LLM's output being correct every time, which is unacceptable for a government citizen-data system. By making Step 4 a pure function with no AI involved, the only way a mapping reaches production is if a human approved it first. The AI's job is strictly "propose," never "decide."

### 4.7 `connector-generator/main.py`

- `POST /generate-connector` → calls `generate_connector_config()`, catches `ValueError` → HTTP 400.
- `GET /health` → same pattern as the other service.

### 4.8 `requirements.txt` files

- `connector-generator/requirements.txt`: `fastapi, uvicorn, pydantic` — no AI dependency at all, which itself is evidence that Step 4 has zero AI involvement (a nice fact to mention proactively).
- `schema-mapper/requirements.txt`: `fastapi, uvicorn, pydantic, gemini` — **note:** the actual import in code is `from google import genai`, which comes from the `google-genai` package on PyPI, not a package literally named `gemini`. This line in `requirements.txt` looks like a typo and should be corrected to `google-genai` before a clean install is attempted elsewhere — worth fixing before your final submission/demo.

### 4.9 `.env`

Holds `GEMINI_API_KEY` (value not reproduced here for security). Loaded via `python-dotenv` so the key never has to be hardcoded or committed to source control — a standard security practice.

## 5. Anticipate the hardest questions

**Q: What happens if the LLM returns garbage or refuses to answer?**
A: `json.loads()` will throw `JSONDecodeError`, which is caught and re-raised as a clear `ValueError` including the raw text — so the caller gets an explicit, debuggable 400-style error rather than a silent wrong answer or a crash deep in the mapping logic.

**Q: How do you stop the AI from hallucinating fields that don't exist?**
A: Every mapping the LLM proposes is checked against the actual `source_fields` and `canonical` dicts before being accepted; anything not present in both is silently dropped. Types are also never taken from the LLM — they're looked up from our own schemas.

**Q: Why two separate microservices instead of one?**
A: They map onto two different points in the pipeline with different trust levels — Step 2/3 (schema-mapper) are AI-assisted and produce *proposals*; Step 4 (connector-generator) only runs after human approval and produces the *final artifact*. Splitting them by service also means they could be scaled/deployed independently (e.g., the AI-calling service might need more careful rate-limiting than the pure-logic one).

**Q: What's the weakest part of your implementation?**
A: The date-detection heuristic in the schema analyzer (`_looks_like_date`) is a simple digit/separator count, not a real date parser, so unusual date formats could be misclassified — acceptable for a prototype but flagged as a known limitation. Also, canonical schemas per service are currently hardcoded in Python rather than stored in a database, so adding a new department service currently requires a code change.

**Q: How would you scale this to more departments/services?**
A: Move `SERVICE_CANONICAL_FIELDS` out of code and into a database or config store keyed by `serviceId`; the rest of the pipeline (`analyze_schema`, `map_schema`, `generate_connector_config`) would not need to change since they already take `canonical_fields`/`service_id` as parameters rather than hardcoding logic per department.

**Q: Why Pydantic/FastAPI specifically, not Flask/Django?**
A: The project depends on several teams agreeing on exact data "contracts" (A, B, C). Pydantic models give free, automatic request/response validation matching those exact contracts, and FastAPI auto-generates interactive API docs from those same models — both directly support the contract-first, multi-team way this project was built.

**Q: What data actually flows into your service and back out, concretely?**
A: See the worked Revenue example in section 4.3 — raw XML in, `{field: type}` out of the analyzer, then that plus a canonical schema in, a validated `MappingResponse` (Contract B) out of the AI mapper, then only the human-approved subset of that in, a final `ConnectorConfig` (Contract C) out of the generator.
