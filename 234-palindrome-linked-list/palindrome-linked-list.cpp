/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
// first just convert the list inot the array and normally check whether its a palindrome or not by using two pointer method.
    bool isPalindrome(ListNode* head) {
        vector<int> arr;
        while(head){
            arr.push_back(head->val);
            head = head->next;
        }
        int left = 0;
        int right = arr.size() - 1;
        while(left < right){
            if(arr[left] != arr[right])
                return false;

            left++;
            right--;
        }
        return true;
    }
};