/*class Solution {
public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        const long long MOD = 1e9 + 7;
        vector<int> final;
        for(int i =0 ;i<queries.size();i++){
            int l = queries[i][0];
            int r = queries[i][1];
            
            long long x =0;
            long long sum =0;
            for(int j = l;j<=r;j++){
                if(s[j] != '0'){
                    int digit = s[j] - '0';
                    x = (x*10+digit)%MOD;
                    sum = sum + digit;
                }
            }
            final.push_back((x * sum) % MOD);
        }
        return final;
    }
};*/
class Solution {
public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        const long long MOD = 1000000007;

        vector<int> pos;          // original positions of non-zero digits
        vector<int> digit;        // non-zero digits
        vector<long long> prefVal(1, 0);
        vector<long long> prefSum(1, 0);
        vector<long long> pow10(1, 1);

        for (int i = 0; i < s.size(); i++) {
            if (s[i] != '0') {
                int d = s[i] - '0';

                pos.push_back(i);
                digit.push_back(d);

                prefVal.push_back((prefVal.back() * 10 + d) % MOD);
                prefSum.push_back(prefSum.back() + d);
                pow10.push_back((pow10.back() * 10) % MOD);
            }
        }

        vector<int> ans;

        for (auto &q : queries) {
            int l = q[0];
            int r = q[1];

            int L = lower_bound(pos.begin(), pos.end(), l) - pos.begin();
            int R = upper_bound(pos.begin(), pos.end(), r) - pos.begin();

            int len = R - L;

            if (len == 0) {
                ans.push_back(0);
                continue;
            }

            long long x = (prefVal[R] - (prefVal[L] * pow10[len]) % MOD + MOD) % MOD;
            long long sum = prefSum[R] - prefSum[L];

            ans.push_back((x * sum) % MOD);
        }

        return ans;
    }
};