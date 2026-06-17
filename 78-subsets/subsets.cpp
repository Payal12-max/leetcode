class Solution {
private:
    void solve(vector<int> nums, vector<int> pset, int index, vector<vector<int>>& ans){
        if(index >= nums.size()){
            ans.push_back(pset);
            return;
        }
        //exclude
        solve(nums,pset,index+1,ans);

        int element = nums[index];
        pset.push_back(element);
        solve(nums, pset, index+1, ans);
    }
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> pset;
        int index = 0;
        solve(nums, pset,index, ans);
        return ans;
    }
};