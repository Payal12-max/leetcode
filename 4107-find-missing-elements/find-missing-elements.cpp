class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        int n = nums.size();

        int start = nums[0];
        vector<int> final;

        for(int i=0;i<n;i++){
            while(start<nums[i]){
                final.push_back(start);
                start++;
            }
            start++;
        }
        return final;
    }
};