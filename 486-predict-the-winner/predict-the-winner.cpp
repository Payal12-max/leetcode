class Solution {
public:
    vector<vector<long long>> memo;

    long long findBestDifference(vector<int>& nums, int left, int right) {
        if (left == right) {
            return nums[left];
        }

        if (memo[left][right] != LLONG_MIN) {
            return memo[left][right];
        }

        long long takeFromLeft =
            nums[left] - findBestDifference(nums, left + 1, right);

        long long takeFromRight =
            nums[right] - findBestDifference(nums, left, right - 1);

        return memo[left][right] = max(takeFromLeft, takeFromRight);
    }

    bool predictTheWinner(vector<int>& nums) {
        int size = nums.size();

        memo.assign(
            size,
            vector<long long>(size, LLONG_MIN)
        );

        long long finalDifference =
            findBestDifference(nums, 0, size - 1);

        return finalDifference >= 0;
    }
};