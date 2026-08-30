class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int mini = INT_MAX;
        int maxi = INT_MIN;
        int n = nums.size();

        int del = 0;
        int minind = -1 , maxind = -1;
        for(int i=0;i<nums.size();i++){
            if(nums[i] < mini){
                mini = nums[i];
                minind = i;
            }

            if(nums[i] > maxi){
                maxi = nums[i];
                maxind = i;
            }
        }

        int delf = max(minind , maxind)+1;
        int delb = n - min(minind,maxind);
        int both = min(minind, maxind) + 1 + n - max(minind, maxind);

        return min({delf,delb, both});
    }
};