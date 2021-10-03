#include<iostream>

using namespace std;

//链表的定义
struct ListNode {
int val;
ListNode* next;
ListNode() : val(0), next(nullptr) {}
ListNode(int x) : val(x), next(nullptr) {}
ListNode(int x, ListNode* next) : val(x), next(next) {}
};

//求用链表表示的整数的和的函数的定义
ListNode* addTwoNumbers(
ListNode* l1, 
ListNode* l2, 
int t = 0 /* t是为了递归调用时可以进行情况分类 */
) 
{
ListNode* l3 = new ListNode;
//情况1：l1和l2最高位相同，但可能产生了进位
if (l1 == nullptr && l2 == nullptr) {
if (t == 1) { /*有进位产生*/
l3->val = 1;
l3->next = nullptr;
return l3;
}
else { /*没有进位产生*/
return nullptr;
}
}
//情况2：l1的位数小于l2
else if (l1 == nullptr) {
int s = l2->val + t; //当前位的和等于当前的值加上进位值
if (s < 10) {
l3->val = s;
l3->next = addTwoNumbers(l1, l2->next, 0);//之后其实仅仅是l2后续位的进位
}   //因此将l1 == nullptr ，l2->传递
else { l3->next = addTwoNumbers(l1, l2->next, 1); }
return l3;
}
//情况3：l2的位数小于l1
else if (l2 == nullptr) {
int s = l1->val + t;
if (s < 10) {
l3->val = s;
l3->next = addTwoNumbers(l1->next, l2, 0);
}
else { l3->next = addTwoNumbers(l1->next, l2, 1); }
return l3;
}

//当前状态不存在位数不同时的处理
int s = l1->val + l2->val + t;
/*无进位*/
if (s < 10) { 
l3->val = s;
l3->next = addTwoNumbers(l1->next, l2->next, 0);
return l3;
}
/*有进位*/
else {
l3->val = s % 10;
l3->next = addTwoNumbers(l1->next, l2->next, 1);
return l3;
}
} 