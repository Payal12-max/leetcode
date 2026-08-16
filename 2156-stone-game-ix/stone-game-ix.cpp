class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {
        int cnt[3] = {0, 0, 0};

        for (int x : stones) {
            cnt[x % 3]++;
        }

        int c0 = cnt[0];
        int c1 = cnt[1];
        int c2 = cnt[2];

        if (c0 % 2 == 0) {
            // Need at least one stone of each non-zero remainder.
            return c1 > 0 && c2 > 0;
        }

        // Odd number of 0-mod-3 stones.
        return abs(c1 - c2) >= 3;
    }
};