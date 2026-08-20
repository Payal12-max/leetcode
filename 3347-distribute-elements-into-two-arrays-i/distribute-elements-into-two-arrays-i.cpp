class Solution {
public:
    vector<int> resultArray(vector<int>& nums) {
        vector<int> sec = {nums[0]};
        vector<int> one = {nums[1]};

        for(int i=2;i<nums.size();i++){
            if(sec.back() > one.back()){
                sec.push_back(nums[i]);
            }else{
                one.push_back(nums[i]);
            }
        }
        vector<int> result = sec;
        result.insert(result.end(), one.begin(), one.end());

        return result;
    }
};