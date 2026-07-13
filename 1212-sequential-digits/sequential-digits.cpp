class Solution {
public:
    vector<int> sequentialDigits(int low, int high) {
        string digits = "123456789";
        vector<int> ans;

        int minLength = to_string(low).length();
        int maxLength = to_string(high).length();

        for (int len = minLength; len <= maxLength; len++) {

            for (int start = 0; start + len <= 9; start++) {

                string current = digits.substr(start, len);
                int number = stoi(current);

                if (number >= low && number <= high) {
                    ans.push_back(number);
                }
            }
        }

        return ans;
    }
};