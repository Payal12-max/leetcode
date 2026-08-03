class Solution {
public:
    string stoneGameIII(vector<int>& stoneValue) {
       int size = stoneValue.size();

       vector<int> dp(size+1,0);

       for(int i=size-1;i>=0;i--){
        int sum = 0;
        dp[i] = INT_MIN;
        
        for (int take = 1; take <= 3 && i + take <= size; take++) {
                sum += stoneValue[i + take - 1];
                dp[i] = max(dp[i], sum - dp[i + take]);
            }
       }
       if(dp[0]>0){
        return "Alice";
       }
       if(dp[0]<0){
        return "Bob";
       }

       return "Tie";
    }
};