class Solution {
public:
    int subsequencePairCount(vector<int>& nums) {
        const int MOD = 1e9 + 7;

        int maxValue = *max_element(nums.begin(), nums.end());

        vector<vector<long long>> dp(
            maxValue + 1,
            vector<long long>(maxValue + 1, 0)
        );

        // Both subsequences are initially empty
        dp[0][0] = 1;

        for (int num : nums) {
            vector<vector<long long>> next = dp;

            for (int g1 = 0; g1 <= maxValue; g1++) {
                for (int g2 = 0; g2 <= maxValue; g2++) {
                    if (dp[g1][g2] == 0)
                        continue;

                    // Add num to seq1
                    int newGcd1 = gcd(g1, num);

                    next[newGcd1][g2] =
                        (next[newGcd1][g2] + dp[g1][g2]) % MOD;

                    // Add num to seq2
                    int newGcd2 = gcd(g2, num);

                    next[g1][newGcd2] =
                        (next[g1][newGcd2] + dp[g1][g2]) % MOD;
                }
            }

            dp = move(next);
        }

        long long answer = 0;

        // g > 0 ensures both subsequences are non-empty
        for (int g = 1; g <= maxValue; g++) {
            answer = (answer + dp[g][g]) % MOD;
        }

        return answer;
    }
};