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

    ListNode* reverse(ListNode* head) {
        ListNode* prev = NULL;
        ListNode* curr = head;

        while(curr) {
            ListNode* nextNode = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextNode;
        }

        return prev;
    }

    ListNode* removeNodes(ListNode* head) {

        head = reverse(head);

        int maxi = head->val;

        ListNode* curr = head;

        while(curr && curr->next) {

            if(curr->next->val < maxi) {
                curr->next = curr->next->next;
            }
            else {
                curr = curr->next;
                maxi = max(maxi, curr->val);
            }
        }

        return reverse(head);
    }
};