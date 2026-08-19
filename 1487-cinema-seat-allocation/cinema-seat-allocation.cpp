class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int, int> mp;

        for (auto &x : reservedSeats)
            mp[x[0]] |= (1 << x[1]);

        long long ans = 2LL * (n - mp.size());

        for (auto &[row, mask] : mp) {
            bool left  = !(mask & ((1 << 2) | (1 << 3) | (1 << 4) | (1 << 5)));
            bool mid   = !(mask & ((1 << 4) | (1 << 5) | (1 << 6) | (1 << 7)));
            bool right = !(mask & ((1 << 6) | (1 << 7) | (1 << 8) | (1 << 9)));

            if (left && right)
                ans += 2;
            else if (left || mid || right)
                ans += 1;
        }

        return ans;
    }
};