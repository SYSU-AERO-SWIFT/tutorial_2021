/*************************************************************************
	> File Name: list_add.cpp
	> Author:ZX Xie 
	> Mail:1514806752@qq.com 
	> Created Time: 2021年10月03日 星期日 20时14分11秒
 ************************************************************************/
#include <iostream>

using namespace std;

//Definition for singly-linked list.
// struct ListNode {
//     int val;
//     ListNode *next;
//     ListNode(int x) : val(x), next(NULL) {}
// };

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    int val1, val2, sum = 0;
    ListNode* head = NULL;
    ListNode* pre = NULL;
    while(1) {
        val1 = val2 = 0;
        if (l1 != NULL) {
            val1 = l1->val;
            l1 = l1->next;
        }
        if (l2 != NULL) {
            val2 = l2->val;
            l2 = l2->next;
        }
        sum += val1 + val2;
        if (sum == 0 && l1 == NULL && l2 == NULL) break;
        ListNode* cur = new ListNode(sum%10);
        if (pre == NULL) head = pre = cur;
        else {
            pre->next = cur;
            pre = cur;
        }
        sum /= 10;
    }
    return head;
}

// int main() {
//     ListNode h11(7);
//     ListNode h12(1);
//     ListNode h13(6);
//     ListNode h21(5);
//     ListNode h22(9);
//     ListNode h23(2);
//     h11.next = &h12;
//     h12.next = &h13;
//     h21.next = &h22;
//     h22.next = &h23;
//     ListNode* ans = addTwoNumbers(&h11, &h21);
//     ListNode* cur = ans;
//     for (;cur != NULL;) {
//         cout << cur->val;
//         cur = cur->next;
//     }
//     return 0;
// }
