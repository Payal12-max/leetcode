class Solution {
public:
// solved by dutch national flag algorithm my three pointers problem
    void sortColors(vector<int>& nums) {
        int i, j , high;
        i=0;
        j=0; 
        high = nums.size()-1;

        while(j<=high){
            if(nums[j] == 0){
                swap(nums[i],nums[j]);
                i++;
                j++;
            }else if(nums[j] == 1){
                j++;
            }else{
                swap(nums[j],nums[high]);
                high--;
            }
        }
    }
};