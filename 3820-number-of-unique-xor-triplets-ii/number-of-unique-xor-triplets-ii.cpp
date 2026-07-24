class Solution {
public:
//standard approach just XOR with itself and then XOR with every other element.
    int uniqueXorTriplets(vector<int>& nums) {
        const int MAX_XOR = 2048;

        vector<bool> pair(MAX_XOR, false);
        vector<bool> triplet(MAX_XOR, false);

        int n = nums.size();

        // Find all possible XOR values of two elements
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                pair[nums[i] ^ nums[j]] = true;
            }
        }

        // Combine every pair XOR with every array element
        for (int value = 0; value < MAX_XOR; value++) {
            if (!pair[value])
                continue;

            for (int x : nums) {
                triplet[value ^ x] = true;
            }
        }

        int count = 0;

        for (bool present : triplet) {
            if (present)
                count++;
        }

        return count;
    }
};