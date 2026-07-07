class Solution {
public:
    long long sumAndMultiply(int n) {
        if (n == 0) return 0;

        vector<int> digits;

        while (n > 0) {
            int d = n % 10;
            if (d != 0)
                digits.push_back(d);
            n /= 10;
        }

        reverse(digits.begin(), digits.end());

        long long x = 0;
        long long sum = 0;

        for (int d : digits) {
            x = x * 10 + d;
            sum += d;
        }

        return x * sum;
    }
};