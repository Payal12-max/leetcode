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
    ListNode* deleteDuplicates(ListNode* head) {
        //kind of traverse the list and thn check the elemt if the next elemt is equal then change the prev pointer to the next value like remove the elemts until a new diff elemt comes up

        ListNode dummy(0);
        dummy.next = head;

        ListNode*prev = &dummy;
        ListNode* curr = head;

        while(curr){
            if(curr->next && curr->val== curr->next->val ){
                int x = curr->val;
                while(curr && curr->val == x){
                    curr = curr->next;
                    prev->next = curr;
                }
            }else{
                prev = curr;
                curr= curr->next;
            }
        }
        return dummy.next;
    }
};