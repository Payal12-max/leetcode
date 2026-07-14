class Solution {
public:
    int numDecodings(string s) {
        int n = s.length();

        if (n == 0 || s[0] == '0') {
            return 0;
        }

        vector<int> dp(n + 1, 0);

        dp[0] = 1;  // Empty string has one way
        dp[1] = 1;  // First character is valid because it is not 0

        for (int i = 2; i <= n; i++) {

            // Check the current single digit
            if (s[i - 1] != '0') {
                dp[i] += dp[i - 1];
            }

            // Form a two-digit number
            int twoDigit =
                (s[i - 2] - '0') * 10 +
                (s[i - 1] - '0');

            if (twoDigit >= 10 && twoDigit <= 26) {
                dp[i] += dp[i - 2];
            }
        }

        return dp[n];
    }
};