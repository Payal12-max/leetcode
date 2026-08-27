class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();

        // Count characters of s
        vector<int> freq(26, 0);
        for (char c : s) {
            freq[c - 'a']++;
        }

        // prefix will store target's prefix that we successfully match
        string prefix = "";

        for (int i = 0; i < n; i++) {

            int x = target[i] - 'a';

            // Option 1:
            // Keep this character equal to target[i].
            if (freq[x] > 0) {
                freq[x]--;
                prefix += target[i];
                continue;
            }

            // We cannot keep target[i].
            // We need to make the answer greater at THIS position
            // or at an earlier position.
            break;
        }

        // The above matching tells us how much of target
        // we could reproduce, but we need to find the RIGHTMOST
        // position where we can make it larger.
        //
        // Rebuild frequencies.
        fill(freq.begin(), freq.end(), 0);
        for (char c : s)
            freq[c - 'a']++;

        for (int i = n - 1; i >= 0; i--) {

            // Check whether target[0..i-1] can be formed.
            vector<int> cnt = freq;
            bool possible = true;

            for (int j = 0; j < i; j++) {
                int c = target[j] - 'a';

                if (cnt[c] == 0) {
                    possible = false;
                    break;
                }

                cnt[c]--;
            }

            if (!possible)
                continue;

            // We now have target[0..i-1].
            // Find smallest available character > target[i].
            int x = target[i] - 'a';

            for (int c = x + 1; c < 26; c++) {

                if (cnt[c] == 0)
                    continue;

                string ans = target.substr(0, i);

                // Make the first difference here.
                ans += char('a' + c);
                cnt[c]--;

                // Remaining characters in sorted order.
                for (int j = 0; j < 26; j++) {
                    while (cnt[j] > 0) {
                        ans += char('a' + j);
                        cnt[j]--;
                    }
                }

                return ans;
            }
        }

        return "";
    }
};