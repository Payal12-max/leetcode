/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
//by storing add of the linkedlist node in the list or by FLOYD CYCLE DETECTION.
    bool hasCycle(ListNode *head) {
        unordered_set<ListNode*> visited;

while(head != NULL){
    if(visited.count(head))
        return true;      // cycle exists

    visited.insert(head);
    head = head->next;
}

return false;
    }
};