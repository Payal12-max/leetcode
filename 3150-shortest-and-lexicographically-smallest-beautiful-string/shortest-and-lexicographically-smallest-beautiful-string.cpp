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

class Solution {
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
};