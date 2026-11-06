class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int left = 1;
        int right = *max_element(piles.begin(),piles.end());

        while(left < right){
            int k = left +(right-left)/2;
            long long hrs = 0;
            for (int pile : piles) {
                hrs += (pile + k - 1) / k;
            }
            
            if (hrs <= h) {
                right = k;      // This speed works; try slower
            } else {
                left = k + 1;   // Too slow; try faster
            }
        }
    return left;
    }
};