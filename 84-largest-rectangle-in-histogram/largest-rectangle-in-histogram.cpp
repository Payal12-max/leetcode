class Solution {
private:
    vector<int> nextSmallerElement(vector<int> &arr, int n){
        stack<int> st;
        vector<int> ans(n);

        st.push(-1);

        for (int i = n - 1; i >= 0; i--) {

            while (st.top() != -1 &&
                   arr[st.top()] >= arr[i]) {
                st.pop();
            }

            ans[i] = st.top();
            st.push(i);
        }

        return ans;
    }
vector<int> previousSmallerIndex(vector<int>& arr, int n) {
        stack<int> st;
        vector<int> ans(n);

        st.push(-1);

        for (int i = 0; i < n; i++) {

            while (st.top() != -1 &&
                   arr[st.top()] >= arr[i]) {
                st.pop();
            }

            ans[i] = st.top();
            st.push(i);
        }

        return ans;
    }
public:
    int largestRectangleArea(vector<int>& heights) {
        //this is the standard brute force approach of this problem. it has a really high tc so to improve this we use stack in this question.
        /*int size = heights.size();
        int area = 0;


        int bth = 1;
        for(int i=0;i<size;){
            int minh = heights[i];
            for(int j=i;j<size;j++){
                minh = min(minh, heights[j]);

                int bth = j-i+1;
                int tarea = minh*bth;


                area = max(area,tarea);
            }
        }
        return area;*/
        int n = heights.size();

        vector<int> next = nextSmallerElement(heights, n);
        vector<int> previous = previousSmallerIndex(heights, n);

        int maxArea = 0;

        for (int i = 0; i < n; i++) {

            // No smaller bar on the right
            if (next[i] == -1) {
                next[i] = n;
            }

            int width = next[i] - previous[i] - 1;
            int area = heights[i] * width;

            maxArea = max(maxArea, area);
        }

        return maxArea;
    }
};