class Solution {
public:
    string processStr(string s) {
        string result;

        for(int i=0;i<s.length();i++){
            if(islower(s[i])){
                result.push_back(s[i]);
            }else if(s[i] != islower(s[i])){
                switch(s[i]){
                case('*'):
                if(!result.empty()){
                    result.pop_back();
                }
                break;
                case('#'):
                if(!result.empty())
                result += result; 
                break;
                case('%'):
                reverse(result.begin(), result.end());
                break;
                }
            }else{
                i++;
            }
        }
        return result;
    }
};