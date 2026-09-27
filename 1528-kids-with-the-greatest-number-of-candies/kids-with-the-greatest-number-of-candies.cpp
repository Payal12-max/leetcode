class Solution {
public:
    vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
        vector<bool> final;

        for(int i=0;i<candies.size();i++){
            int newii = candies[i]+extraCandies;

            if(newii >= *max_element(candies.begin(), candies.end())){
                final.push_back(true);
            }else{
                final.push_back(false);
            }
        }

        return final;
    }
};