class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.size();

        // Count frequencies
        vector<int> freq(26, 0);

        for (char c : s) {
            freq[c - 'a']++;
        }

        // Check whether a palindrome is possible
        int odd = 0;
        char middle = 0;

        for (int i = 0; i < 26; i++) {
            if (freq[i] % 2 == 1) {
                odd++;
                middle = char('a' + i);
            }
        }

        if (odd > 1) {
            return "";
        }

        // Frequency of characters in the LEFT HALF
        vector<int> halfFreq(26);

        for (int i = 0; i < 26; i++) {
            halfFreq[i] = freq[i] / 2;
        }

        int halfLen = n / 2;

        // Construct palindrome from left half
        auto makePalindrome = [&](const string& left) {
            string right = left;
            reverse(right.begin(), right.end());

            if (n % 2 == 1) {
                return left + string(1, middle) + right;
            }

            return left + right;
        };

        string answer = "";

        // We only need to consider the first half of target.
        string targetLeft = target.substr(0, halfLen);

        /*
            Try making the left half larger than targetLeft
            at every possible position.
        */
        for (int pos = 0; pos < halfLen; pos++) {

            vector<int> cnt = halfFreq;

            string candidate;

            // Match targetLeft before pos
            bool possible = true;

            for (int i = 0; i < pos; i++) {
                int c = targetLeft[i] - 'a';

                if (cnt[c] == 0) {
                    possible = false;
                    break;
                }

                candidate += targetLeft[i];
                cnt[c]--;
            }

            if (!possible) {
                continue;
            }

            // At pos, choose the smallest character
            // greater than targetLeft[pos].
            int x = targetLeft[pos] - 'a';

            for (int c = x + 1; c < 26; c++) {

                if (cnt[c] == 0) {
                    continue;
                }

                string left = candidate;

                left += char('a' + c);

                cnt[c]--;

                // Fill remaining positions with smallest
                // possible characters.
                for (int j = 0; j < 26; j++) {
                    while (cnt[j] > 0) {
                        left += char('a' + j);
                        cnt[j]--;
                    }
                }

                string pal = makePalindrome(left);

                if (pal > target) {

                    if (answer.empty() || pal < answer) {
                        answer = pal;
                    }
                }
            }
        }

        /*
            Also check the case where the left half is
            exactly equal to targetLeft.

            The middle/right side may make the palindrome
            greater than target.
        */
        {
            vector<int> cnt = halfFreq;

            string left;
            bool possible = true;

            for (char ch : targetLeft) {

                int c = ch - 'a';

                if (cnt[c] == 0) {
                    possible = false;
                    break;
                }

                left += ch;
                cnt[c]--;
            }

            if (possible) {

                string pal = makePalindrome(left);

                if (pal > target) {

                    if (answer.empty() || pal < answer) {
                        answer = pal;
                    }
                }
            }
        }

        return answer;
    }
};