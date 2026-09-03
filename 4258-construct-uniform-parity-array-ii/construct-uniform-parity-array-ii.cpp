class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        int minOdd = INT_MAX;

        // Find the smallest odd number
        for (int x : nums1) {
            if (x % 2 == 1) {
                minOdd = min(minOdd, x);
            }
        }

        bool allOdd = true;
        bool allEven = true;

        for (int x : nums1) {
            if (x % 2 == 0) {
                // To make even number odd:
                // x - odd = odd
                if (minOdd >= x)
                    allOdd = false;
            } 
            else {
                // Odd number can stay odd.
            }

            if (x % 2 == 1) {
                // To make odd number even:
                // x - odd = even
                if (minOdd >= x)
                    allEven = false;
            }
            // Even number can stay even.
        }

        return allOdd || allEven;
    }
};