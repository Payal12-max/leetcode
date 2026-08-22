class Solution {
public:
    bool checkDivisibility(int n) {
        int num = n;
        int sum =0;
        int prod = 1;

        while(n != 0){
            sum += n%10;
            prod *= n%10;

            n = n/10;
        }
        int fsum = sum+prod;

        return num % fsum == 0;
    }
};