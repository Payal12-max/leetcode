class Solution {
public:
    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adj(n);
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
        vector<int> vis(n, 0);
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (vis[i]) continue;
            vector<int> comp;
            queue<int> q;
            q.push(i);
            vis[i] = 1;
            while (!q.empty()) {
                int u = q.front(); q.pop();
                comp.push_back(u);
                for (int v : adj[u]) {
                    if (!vis[v]) {
                        vis[v] = 1;
                        q.push(v);
                    }
                }
            }
            int V = comp.size();
            long long E = 0;
            for (int u : comp) E += adj[u].size();
            E /= 2;
            if (E == (long long)V * (V - 1) / 2) count++;
        }
        return count;
    }
};