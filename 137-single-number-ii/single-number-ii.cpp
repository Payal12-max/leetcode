class Solution {
public:
    int singleNumber(vector<int>& nums) {
        unordered_map<int,int> mp;
        for(int x:nums){
            mp[x]++;
        }
        for(int i=0;i<nums.size();i++){
            int q = nums[i];
            if(mp[q] == 1){
                return q;
            }
        }
        return -1;
    }
};