class Solution {
public:

//here if alice chooses 1 elemt as in range[1,2] then she will give other to choose 1 elemt from same [1,2] but if alice choose 2 elemt, then other can choose from [1,4].
    int n;
    vector<int> suffix;
    vector<vector<int>> dp;

    int solve(int i, int M, vector<int>& piles) {
        // All piles have been taken
        if (i >= n)
            return 0;

        // Already calculated
        if (dp[i][M] != -1)
            return dp[i][M];

        int ans = 0;

        // Can take X piles, where 1 <= X <= 2*M
        for (int X = 1; X <= 2 * M && i + X <= n; X++) {

            // Stones Alice takes now
            int taken = suffix[i] - suffix[i + X];

            // Bob plays optimally from i + X
            int bobGets = solve(i + X, max(M, X), piles);

            // Total stones remaining from i
            int totalRemaining = suffix[i];

            // If Bob can get bobGets, we get the rest
            int aliceGets = totalRemaining - bobGets;

            ans = max(ans, aliceGets);
        }

        return dp[i][M] = ans;
    }

    int stoneGameII(vector<int>& piles) {
        n = piles.size();

        // suffix[i] = sum of piles from i to n-1
        suffix.resize(n + 1, 0);

        for (int i = n - 1; i >= 0; i--) {
            suffix[i] = suffix[i + 1] + piles[i];
        }

        dp.assign(n, vector<int>(n + 1, -1));

        return solve(0, 1, piles);
    }
};