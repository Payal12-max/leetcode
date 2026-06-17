class Solution {
public:
    char processStr(string s, long long k) {

        int n = s.size();
        vector<long long> len(n);

        long long cur = 0;

        for (int i = 0; i < n; i++) {

            if (islower(s[i])) {
                cur++;
            }
            else if (s[i] == '*') {
                if (cur > 0) cur--;
            }
            else if (s[i] == '#') {
                cur *= 2;
            }
            else { // %
                // length unchanged
            }

            len[i] = cur;
        }

        if (k >= cur) return '.';

        for (int i = n - 1; i >= 0; i--) {

            long long before =
                (i == 0 ? 0 : len[i - 1]);

            if (islower(s[i])) {

                if (k == before)
                    return s[i];

            }
            else if (s[i] == '#') {

                k %= before;
            }
            else if (s[i] == '%') {

                k = before - 1 - k;
            }
            else { // '*'
                // nothing to do
            }
        }

        return '.';
    }
};