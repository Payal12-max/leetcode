class Solution {
public:
    vector<vector<int>> generate(int numRows) {

        vector<vector<int>> ans;

        for (int i = 0; i < numRows; i++) {

            // Create current row with all 1's
            vector<int> row(i + 1, 1);

            // Fill middle elements
            for (int j = 1; j < i; j++) {
                row[j] = ans[i - 1][j - 1] + ans[i - 1][j];
            }

            ans.push_back(row);
        }

        return ans;
    }
};