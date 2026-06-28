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
    ListNode* swapNodes(ListNode* head, int k) {
        //this is simply done by like find normally first elemt and kth node elemt from end by two pointer so then we will swap the values.
        ListNode* curr = head;
        for (int i = 1; i < k; i++) {
            curr = curr->next;
        }

        ListNode* fast = curr;
        ListNode* slow = head;

        while(fast->next != NULL){
            slow = slow->next;
            fast = fast->next;
        }

        swap(curr->val , slow->val);
        return head;
    }
};