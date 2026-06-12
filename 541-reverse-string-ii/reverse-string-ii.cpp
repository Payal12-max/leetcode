class Solution {
public:
    string reverseStr(string s, int k) {
        int n = s.size();
        for (int i = 0; i < n; i += 2 * k) {
        // reverse first k characters in this block
        int start = i;
        int end = min(i + k - 1, n - 1);

        reverse(s.begin() + start, s.begin() + end + 1);
        }
        return s;
    }
};