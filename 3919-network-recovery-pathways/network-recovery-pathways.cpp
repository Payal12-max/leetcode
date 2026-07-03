class Solution {
public:
    bool can(int score, vector<vector<int>>& edges, vector<bool>& online, long long k, int n) {
        vector<vector<pair<int,int>>> adj(n);
        vector<int> indeg(n, 0);

        for (auto &e : edges) {
            int u = e[0], v = e[1], cost = e[2];

            if (cost < score) continue;

            // intermediate offline nodes not allowed
            if (!online[u] || !online[v]) continue;

            adj[u].push_back({v, cost});
            indeg[v]++;
        }

        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (indeg[i] == 0) q.push(i);
        }

        vector<int> topo;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            topo.push_back(node);

            for (auto &[nbr, cost] : adj[node]) {
                indeg[nbr]--;
                if (indeg[nbr] == 0) q.push(nbr);
            }
        }

        const long long INF = 4e18;
        vector<long long> dist(n, INF);
        dist[0] = 0;

        for (int u : topo) {
            if (dist[u] == INF) continue;

            for (auto &[v, cost] : adj[u]) {
                if (dist[u] + cost < dist[v]) {
                    dist[v] = dist[u] + cost;
                }
            }
        }

        return dist[n - 1] <= k;
    }

    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        int n = online.size();

        int low = 0, high = 0;
        for (auto &e : edges) {
            high = max(high, e[2]);
        }

        int ans = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (can(mid, edges, online, k, n)) {
                ans = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return ans;
    }
};