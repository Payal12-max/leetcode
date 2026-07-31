class Solution {
public:
//more of like total letters = 26, so no. start from 1-9 means total 8, so first 8 = 1 push , 2nd 8 = 2 pushes, 3rd 8 = 3 pushes, 4th 2 = 4 pushes. 
    int minimumPushes(string word) {
        vector<int> freq(26,0);

        for(char ch: word){
            freq[ch-'a']++;
        }

        sort(freq.rbegin(),freq.rend());

        int pushes = 0;

        for(int i=0;i<26;i++){
            int pushcnt = (i/8)+1;
            pushes += freq[i] * pushcnt;
        }

        return pushes;
    }
};