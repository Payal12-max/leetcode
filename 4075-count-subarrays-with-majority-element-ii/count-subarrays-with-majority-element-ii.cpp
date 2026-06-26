class Solution {
public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
                int n = nums.size();

        vector<int> pref(n + 1);
        for (int i = 0; i < n; i++) {
            pref[i + 1] = pref[i] + (nums[i] == target ? 1 : -1);
        }

        // Coordinate compression
        vector<int> vals = pref;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());

        int m = vals.size();
        vector<int> bit(m + 1);

        auto update = [&](int i) {
            while (i <= m) {
                bit[i]++;
                i += i & -i;
            }
        };

        auto query = [&](int i) {
            int ans = 0;
            while (i > 0) {
                ans += bit[i];
                i -= i & -i;
            }
            return ans;
        };

        long long ans = 0;

        for (int x : pref) {
            int id = lower_bound(vals.begin(), vals.end(), x)
                     - vals.begin() + 1;

            // count previous prefix sums < x
            ans += query(id - 1);

            update(id);
        }

        return ans;
    }
};