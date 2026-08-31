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
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        
        vector<int> critical;
        
        int pos = 1;
        
        ListNode* prev = head;
        ListNode* curr = head->next;
        
        while (curr != nullptr && curr->next != nullptr) {
            
            ListNode* next = curr->next;
            
            // Local maximum
            if (curr->val > prev->val && curr->val > next->val) {
                critical.push_back(pos);
            }
            
            // Local minimum
            else if (curr->val < prev->val && curr->val < next->val) {
                critical.push_back(pos);
            }
            
            prev = curr;
            curr = next;
            pos++;
        }
        
        // Fewer than 2 critical points
        if (critical.size() < 2) {
            return {-1, -1};
        }
        
        int minDistance = INT_MAX;
        
        // Only consecutive critical points
        for (int i = 1; i < critical.size(); i++) {
            minDistance = min(minDistance, critical[i] - critical[i - 1]);
        }
        
        // First and last critical points
        int maxDistance = critical.back() - critical.front();
        
        return {minDistance, maxDistance};
    }
};