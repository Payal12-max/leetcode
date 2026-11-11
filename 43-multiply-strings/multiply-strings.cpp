#include <string>
using namespace std;

class Solution {
public:
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0") {
            return "0";
        }

        int n = num1.size();
        int m = num2.size();
        string result(n + m, '0');

        // Multiply each pair of digits, from right to left.
        for (int i = n - 1; i >= 0; --i) {
            for (int j = m - 1; j >= 0; --j) {
                int product = (num1[i] - '0') * (num2[j] - '0');

                int position = i + j + 1;
                int sum = product + (result[position] - '0');

                result[position] = '0' + (sum % 10);
                result[position - 1] += sum / 10;
            }
        }

        // Remove leading zeros.
        int first = 0;
        while (first < result.size() && result[first] == '0') {
            ++first;
        }

        return result.substr(first);
    }
};