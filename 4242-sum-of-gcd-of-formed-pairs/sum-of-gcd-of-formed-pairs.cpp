class Solution {
public:
    long long gcdSum(vector<int>& nums) {
        int n = nums.size();

        vector<int> prefixGcd(n);

        int maximumSoFar = 0;

        for (int i = 0; i < n; i++) {
            maximumSoFar = max(maximumSoFar, nums[i]);
            prefixGcd[i] = gcd(nums[i], maximumSoFar);
        }

        sort(prefixGcd.begin(), prefixGcd.end());

        long long answer = 0;

        int left = 0;
        int right = n - 1;

        while (left < right) {
            answer += gcd(prefixGcd[left], prefixGcd[right]);
            left++;
            right--;
        }

        return answer;
    }
};