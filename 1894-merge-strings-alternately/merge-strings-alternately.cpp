class Solution {
public:
    string mergeAlternately(string word1, string word2) {
        string f1;

        int len1 = word1.length();
        int len2 = word2.length();

        int i = 0;

        while(i < len1 && i < len2) {
            f1.push_back(word1[i]);
            f1.push_back(word2[i]);
            i++;
        }

        while(i < len1) {
            f1.push_back(word1[i]);
            i++;
        }

        while(i < len2) {
            f1.push_back(word2[i]);
            i++;
        }

        return f1;
    }
};