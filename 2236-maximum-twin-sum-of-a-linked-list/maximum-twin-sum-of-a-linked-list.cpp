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
    int pairSum(ListNode* head) {
        vector<int> values;

        for (ListNode* current = head; current != nullptr; current = current->next) {
            values.push_back(current->val);
        }

        int maxSum = 0;
        int n = values.size();

        for (int i = 0; i < n / 2; ++i) {
            maxSum = max(maxSum, values[i] + values[n - 1 - i]);
        }

        return maxSum;
    }
};