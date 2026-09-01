class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        // Give every litter cell an index
        vector<vector<int>> id(m, vector<int>(n, -1));

        int litterCount = 0;
        int sr = 0, sc = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (classroom[i][j] == 'S') {
                    sr = i;
                    sc = j;
                }

                if (classroom[i][j] == 'L') {
                    id[i][j] = litterCount++;
                }
            }
        }

        // All litter collected
        int allMask = (1 << litterCount) - 1;

        // State = row, col, remaining energy, collected litter mask
        struct State {
            int r, c;
            int energy;
            int mask;
        };

        queue<State> q;

        // visited[r][c][energy][mask]
        vector<vector<vector<vector<bool>>>> visited(
            m,
            vector<vector<vector<bool>>>(
                n,
                vector<vector<bool>>(
                    energy + 1,
                    vector<bool>(1 << litterCount, false)
                )
            )
        );

        q.push({sr, sc, energy, 0});
        visited[sr][sc][energy][0] = true;

        int moves = 0;

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        while (!q.empty()) {

            int sz = q.size();

            // All states in this level require 'moves' moves
            while (sz--) {

                State cur = q.front();
                q.pop();

                // Have we collected everything?
                if (cur.mask == allMask) {
                    return moves;
                }

                // If no energy, we cannot move
                if (cur.energy == 0)
                    continue;

                for (int d = 0; d < 4; d++) {

                    int nr = cur.r + dr[d];
                    int nc = cur.c + dc[d];

                    // Outside grid
                    if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                        continue;

                    // Obstacle
                    if (classroom[nr][nc] == 'X')
                        continue;

                    // Moving costs 1 energy
                    int newEnergy = cur.energy - 1;

                    // Collect litter if this cell contains L
                    int newMask = cur.mask;

                    if (classroom[nr][nc] == 'L') {
                        int idx = id[nr][nc];
                        newMask |= (1 << idx);
                    }

                    // Reset energy if we reach R
                    if (classroom[nr][nc] == 'R') {
                        newEnergy = energy;
                    }

                    // Already visited this exact state
                    if (visited[nr][nc][newEnergy][newMask])
                        continue;

                    visited[nr][nc][newEnergy][newMask] = true;

                    q.push({
                        nr,
                        nc,
                        newEnergy,
                        newMask
                    });
                }
            }

            moves++;
        }

        return -1;
    }
};