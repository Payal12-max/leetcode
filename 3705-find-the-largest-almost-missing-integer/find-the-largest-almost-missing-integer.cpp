//this is my version but failed at a test case because i used fq[nums[i]] == 1
/*class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        vector<int> val;

        unordered_map<int,int> fq;
        for(int i=0;i<=nums.size()-k;i++){
            for(int j=i;j<i+k;j++){
                fq[nums[j]]++;
            }
        }
        for(int i=0;i<nums.size();i++){
            if(fq[nums[i]] == 1) {
                val.push_back(nums[i]);
            }
        }
        if(val.empty()) return -1;

        int mx = *max_element(val.begin(), val.end());
        return mx;
    }
};*/

class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        vector<int> val;
        unordered_map<int, int> fq;

        for(int i = 0; i <= nums.size() - k; i++) {
            unordered_set<int> seen;

            for(int j = i; j < i + k; j++) {
                seen.insert(nums[j]);
            }

            for(auto x : seen) {
                fq[x]++;
            }
        }

        for(int i = 0; i < nums.size(); i++) {
            if(fq[nums[i]] == 1) {
                val.push_back(nums[i]);
            }
        }

        if(val.empty()) return -1;

        return *max_element(val.begin(), val.end());
    }
};