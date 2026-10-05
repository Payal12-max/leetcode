class Solution {
public:
// with this approach my 78/87 cases were passed.but TLE
    int searchR(vector<int>& nums,int i1, int i2,int num1){
        for(int i = i1;i<=i2;i++){
            if(nums[i]>num1){
                return i;
            }
        }
        return -1;
    }
    int searchL(vector<int>& nums,int in1, int in2,int num2){
        for(int i = in1;i>=in2;i--){
            if(nums[i]<num2){
                return i;
            }
        }
        return -1;
    }
    //this is the initial approach i came up with and passed only 8 testcases out of 87
    bool increasingTriplet(vector<int>& nums) { 

        /*int x = searchR(nums, 0, nums.size() - 1, nums[0]);
        if (x != -1) {
            int y = searchR(nums, x+1, nums.size() - 1, nums[x]);
            if (y != -1) {
                return true;
            }
        }
        for (int i = 1; i < nums.size(); i++) {
            int a = searchL(nums, i - 1, 0, nums[i]);
            int b = searchR(nums, i + 1, nums.size() - 1, nums[i]);
            
            if (a != -1 && b != -1) {
                return true;
            }
        }
        return false;*/
        
        int first = INT_MAX;
        int second = INT_MAX;

        for (int x : nums) {

            if (x <= first) {
                first = x;
            }
            else if (x <= second) {
                second = x;
            }
            else {
                return true;
            }
        }

        return false;
    }
};