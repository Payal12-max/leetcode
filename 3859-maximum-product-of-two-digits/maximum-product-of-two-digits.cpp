class Solution {
public:
    int maxProduct(int n) {
        int max1 = -1;
        int max2 = -1;

        while(n>0){
            int digi = n%10;

            if(digi >= max1){
                max2 = max1;
                max1 = digi;
            } else if (digi > max2) {
                max2 = digi;
            }
            n /= 10;
        }

        return max1*max2;
    }
};