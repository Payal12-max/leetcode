//the brute force appraoch-
/*class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        vector<string> ans;
        int n = s.length();
        for(int i=0;i<n;i++){
            for(int j = i;j<n;j++){
                int freq = count(s.begin()+i,s.begin()+j+1,'1');
                if(freq == k){
                    string sub = s.substr(i, j - i + 1); // Store the substring ans.push_back(sub);
                    ans.push_back(sub);
                }
            }
        }
        if (ans.empty()) return "";
        string result = ans[0]; 
        for (string sub : ans) { 
            if (sub.length() < result.length()){ 
                result = sub; 
            } else if (sub.length() == result.length() && sub < result){
                result = sub;
            }
        } 
        return result;
    }
};*/
//On^2 sol
/*class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int n = s.length();

        int left = 0;
        int ones = 0;

        string result = "";

        for (int right = 0; right < n; right++) {

            // Add current character
            if (s[right] == '1')
                ones++;

            // If we have exactly k ones,
            // try shrinking from the left
            while (ones == k) {

                string sub = s.substr(left, right - left + 1);

                // Update answer
                if (result == "" ||
                    sub.length() < result.length() ||
                    (sub.length() == result.length() && sub < result)) {
                    result = sub;
                }

                // Remove left character
                if (s[left] == '1')
                    ones--;

                left++;
            }
        }

        return result;
    }
};*/

class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        vector<int> pos;

        // Store positions of all 1s
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '1') {
                pos.push_back(i);
            }
        }

        if (pos.size() < k)
            return "";

        string ans = "";

        // Take every group of k consecutive 1s
        for (int i = 0; i + k - 1 < pos.size(); i++) {

            int left = pos[i];
            int right = pos[i + k - 1];

            string sub = s.substr(left, right - left + 1);

            if (ans == "" ||
                sub.length() < ans.length() ||
                (sub.length() == ans.length() && sub < ans)) {
                ans = sub;
            }
        }

        return ans;
    }
};