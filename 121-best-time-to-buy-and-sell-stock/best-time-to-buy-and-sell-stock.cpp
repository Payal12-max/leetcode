class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int low = INT_MAX;
        int profit = 0;
        int n = prices.size();
        for(int i=0;i<n;i++){
            low = min(low,prices[i]);

            profit = max(profit, prices[i]-low);
        }
        return profit;
    }
};