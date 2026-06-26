/**
 * Definition for singly-linked list.
 * struct ListListNode {
 *     int val;
 *     ListListNode *next;
 *     ListListNode() : val(0), next(nullptr) {}
 *     ListListNode(int x) : val(x), next(nullptr) {}
 *     ListListNode(int x, ListListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(head == NULL){
            return head;
        }
        ListNode* temp = head;
        while(temp != NULL && temp->next != NULL){
            if(temp->val == temp -> next->val){
                ListNode* dup = temp->next;
                temp -> next = dup->next;
                delete dup;
            }else{
                temp = temp->next;
            }
        }
        return head;
    }
};