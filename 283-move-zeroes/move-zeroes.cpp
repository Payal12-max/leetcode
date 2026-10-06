class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        //this was first approach i came up with but due to ERASE it gave TLE so another approach is shift nonzero digits by the zeros present at front.
        /*for(int i=0;i<nums.size();){
            if(nums[i] == 0){
                nums.push_back(nums[i]);
                nums.erase(nums.begin() + i);
            }else{
                i++;
            }
        }*/
        int j=0;
        for(int i=0;i<nums.size();i++){
            if(nums[i] != 0){
                swap(nums[i], nums[j]);
                j++;
            }
        }
    } 
};