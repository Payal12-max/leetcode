#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string smallestPalindrome(string s) {
        vector<int> freq(26, 0);

        for (char ch : s) {
            freq[ch - 'a']++;
        }

        string left = "";
        char middle = '\0';

        for (int i = 0; i < 26; i++) {
            // Put half of each character in the left side
            left.append(freq[i] / 2, char('a' + i));

            // A palindrome can have at most one odd-frequency character
            if (freq[i] % 2 == 1) {
                middle = char('a' + i);
            }
        }

        string right = left;
        reverse(right.begin(), right.end());

        if (middle != '\0') {
            return left + middle + right;
        }

        return left + right;
    }
};