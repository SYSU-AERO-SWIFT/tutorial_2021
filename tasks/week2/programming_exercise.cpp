#include <iostream>
#include <cstdio>
using namespace std;

ListNode * add(ListNode * l1,ListNode * l2,bool cr){
    if (l1 == NULL)
    {
        return NULL;
    }
    
    int x = (l1 ->val+ l2->val + cr) % 10;
    ListNode *tmp = new ListNode(x);
    bool cr_tmp = ((l1->val + l2->val) / 10);
    
    tmp->next = add(l1->next,l2->next,cr_tmp);
    ListNode * t = tmp;
    return t;
}
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2){
    if (l1 == NULL)
    {
        return NULL;
    }
    return add(l1,l2,false);
}
