class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int x = 0;
        bool nonZero = false;

        for (int num : nums) {
            x ^= num;
            if (num != 0)
                nonZero = true;
        }

        if (x != 0)
            return nums.size();

        if (nonZero)
            return nums.size() - 1;

        return 0;
    }
};
