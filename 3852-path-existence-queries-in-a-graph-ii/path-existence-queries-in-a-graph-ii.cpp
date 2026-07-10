class Solution {
public:
    vector<int> pathExistenceQueries(
        int n,
        vector<int>& nums,
        int maxDiff,
        vector<vector<int>>& queries
    ) {
        // Store {value, original index}
        vector<pair<int, int>> nodes;
        
        for (int i = 0; i < n; i++) {
            nodes.push_back({nums[i], i});
        }

        sort(nodes.begin(), nodes.end());

        vector<int> values(n);
        vector<int> position(n);

        for (int i = 0; i < n; i++) {
            values[i] = nodes[i].first;
            position[nodes[i].second] = i;
        }

        // Identify connected components
        vector<int> component(n, 0);

        for (int i = 1; i < n; i++) {
            component[i] = component[i - 1];

            if (values[i] - values[i - 1] > maxDiff) {
                component[i]++;
            }
        }

        // farthest[i] = farthest position reachable from i in one edge
        vector<int> farthest(n);
        int right = 0;

        for (int left = 0; left < n; left++) {
            right = max(right, left);

            while (right + 1 < n &&
                   values[right + 1] - values[left] <= maxDiff) {
                right++;
            }

            farthest[left] = right;
        }

        // Binary lifting
        int LOG = 1;

        while ((1 << LOG) <= n) {
            LOG++;
        }

        vector<vector<int>> jump(LOG, vector<int>(n));

        for (int i = 0; i < n; i++) {
            jump[0][i] = farthest[i];
        }

        for (int level = 1; level < LOG; level++) {
            for (int i = 0; i < n; i++) {
                jump[level][i] =
                    jump[level - 1][jump[level - 1][i]];
            }
        }

        vector<int> answer;

        for (vector<int>& query : queries) {
            int u = position[query[0]];
            int v = position[query[1]];

            if (u == v) {
                answer.push_back(0);
                continue;
            }

            if (u > v) {
                swap(u, v);
            }

            // No path exists
            if (component[u] != component[v]) {
                answer.push_back(-1);
                continue;
            }

            int current = u;
            int distance = 0;

            // Make the largest jumps that remain before v
            for (int level = LOG - 1; level >= 0; level--) {
                int next = jump[level][current];

                if (next > current && next < v) {
                    current = next;
                    distance += (1 << level);
                }
            }

            // One final edge reaches v
            answer.push_back(distance + 1);
        }

        return answer;
    }
};