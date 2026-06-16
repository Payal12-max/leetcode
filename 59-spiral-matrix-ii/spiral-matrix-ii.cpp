class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> mat(n, vector<int>(n));

        int top = 0;
        int bottom = n - 1;
        int left = 0;
        int right = n - 1;

        int num = 1;

        while (top <= bottom && left <= right) {

            for (int j = left; j <= right; j++)
                mat[top][j] = num++;
            top++;

            for (int i = top; i <= bottom; i++)
                mat[i][right] = num++;
            right--;

            for (int j = right; j >= left && top <= bottom; j--)
                mat[bottom][j] = num++;
            bottom--;

            for (int i = bottom; i >= top && left <= right; i--)
                mat[i][left] = num++;
            left++;
        }

        return mat;
    }
};