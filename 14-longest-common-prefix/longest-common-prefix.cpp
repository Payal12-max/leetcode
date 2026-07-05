class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.empty()){
            return "";
        }
        else{
            string fir=strs[0];
            for(int i=1;i<strs.size();i++){
                while(strs[i].find(fir)!=0){
                    fir=fir.substr(0,fir.length() -1);
                    
                    if(fir.empty())
                    return "";
                }
            }
            return fir;
        }
    }
};