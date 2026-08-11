class Solution {
private:
    int isvalid(vector<int> nums){
        int sum = nums[0];
        for(int j=1;j<nums.size();j++){
            if(nums[j] == nums[j-1]+1){
                sum += nums[j];
            }else{
                break;
            }
        }
        return sum;
    }
public:
    int missingInteger(vector<int>& nums) {
        int num = isvalid(nums);
        unordered_set<int> st(nums.begin(), nums.end());

        while (st.count(num)) {
            num++;
        }

        return num;
    }
};