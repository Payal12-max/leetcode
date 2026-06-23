class Solution {
public:
    static const int MOD = 1000000007;

    int zigZagArrays(int n, int l, int r) {

        int m = r - l + 1;

        // Special case: length 2 is not possible according to constraints,
        // but this makes the function complete.
        if (n == 1) return m;
        if (n == 2) return 1LL * m * (m - 1) % MOD;

        vector<int> up(m + 2, 0), down(m + 2, 0);
        vector<int> newUp(m + 2, 0), newDown(m + 2, 0);
        vector<int> pref(m + 2, 0), suff(m + 2, 0);

        // Arrays of length 2
        for (int v = 1; v <= m; v++) {
            up[v] = v - 1;
            down[v] = m - v;
        }

        for (int len = 3; len <= n; len++) {

            pref[0] = 0;
            for (int i = 1; i <= m; i++) {
                pref[i] = pref[i - 1] + down[i];
                if (pref[i] >= MOD) pref[i] -= MOD;
            }

            suff[m + 1] = 0;
            for (int i = m; i >= 1; i--) {
                suff[i] = suff[i + 1] + up[i];
                if (suff[i] >= MOD) suff[i] -= MOD;
            }

            for (int v = 1; v <= m; v++) {
                newUp[v] = pref[v - 1];
                newDown[v] = suff[v + 1];
            }

            swap(up, newUp);
            swap(down, newDown);
        }

        long long ans = 0;
        for (int v = 1; v <= m; v++) {
            ans += up[v];
            ans += down[v];
            ans %= MOD;
        }

        return (int)ans;
    }
};