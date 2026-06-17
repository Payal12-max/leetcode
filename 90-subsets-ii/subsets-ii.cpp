class Solution {
private:
    void solve(vector<int>& nums,vector<int> output, int index, vector<vector<int>>& ans){
        if(index >= nums.size()){
            ans.push_back(output);
            return;
        }

                // Include
        int ele = nums[index];
        output.push_back(ele);
        solve(nums, output, index+1, ans);
        output.pop_back();

        // Exclude current and all duplicates
        while(index + 1 < nums.size() && nums[index] == nums[index + 1])
            index++;

        solve(nums, output, index+1,ans);
    }
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> output;

        int index=0;
        sort(nums.begin(),nums.end());
        solve(nums, output, index,ans);

        return ans;
    }
};