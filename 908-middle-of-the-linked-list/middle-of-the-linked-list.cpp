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
private: 
int len(ListNode* head){
    int cnt = 0;
    while(head != nullptr){
        cnt++;
        head = head->next;           
    }
    return cnt;
}
public:
    ListNode* middleNode(ListNode* head) {
        ListNode* temp = head;
        int n = len(temp);
        int ans = n/2 ;
        int cnt = 0;
        while(cnt<ans){
            temp = temp->next;
            cnt++;
        }
        return temp;
    }
};