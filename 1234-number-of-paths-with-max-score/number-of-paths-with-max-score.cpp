//for this question im thinking of doing like ill start at board[i][j] and first ill assign path as0 and sum = 0; then ill traverse the 2d matrix and check if either board[i-1[j-1] is X or board[i][j-1] is X or board[i-1][j] is X or any of them is X if yes then skip that and chekc max of remaining which is max take that and add in sum and repeat until you reach board[0][0] like this an dwe will do path++ too to find out path no. and return them in vector format like [,]? or should i use backtracking but like i dont think it will work?// this is like the ideal appoarch i cna think of but it will fail at some point because it doesnot need greedy as the max no. wont lead to best path , "SO USE DP INSTEAD OF THIS."

class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        int n = board.size();
        int MOD = 1e9 + 7;

        vector<vector<int>> sum(n, vector<int>(n, -1));
        vector<vector<int>> ways(n, vector<int>(n, 0));

        sum[n-1][n-1] = 0;
        ways[n-1][n-1] = 1;

        for (int i = n - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {

                if (board[i][j] == 'X') continue;
                if (i == n - 1 && j == n - 1) continue;

                int best = -1;
                int count = 0;

                int dr[3] = {1, 0, 1};
                int dc[3] = {0, 1, 1};

                for (int k = 0; k < 3; k++) {
                    int ni = i + dr[k];
                    int nj = j + dc[k];

                    if (ni < n && nj < n && sum[ni][nj] != -1) {
                        if (sum[ni][nj] > best) {
                            best = sum[ni][nj];
                            count = ways[ni][nj];
                        }
                        else if (sum[ni][nj] == best) {
                            count = (count + ways[ni][nj]) % MOD;
                        }
                    }
                }

                if (best == -1) continue;

                int val = 0;
                if (board[i][j] >= '0' && board[i][j] <= '9') {
                    val = board[i][j] - '0';
                }

                sum[i][j] = best + val;
                ways[i][j] = count;
            }
        }

        if (ways[0][0] == 0) return {0, 0};

        return {sum[0][0], ways[0][0]};
    }
};