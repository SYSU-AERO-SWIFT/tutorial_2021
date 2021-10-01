 #include <iostream>
using namespace std;

//定义节点
struct ListNode{
    int val;
    ListNode* next;
    ListNode(int x) :val(x), next(nullptr) {}
 };

using namespace std;
ListNode* addTwoNumber(ListNode* l1, ListNode* l2);
int main()
{
   /* 测试例子
   ListNode* l1 = new ListNode(9);
    //l1->next = new ListNode(9);
    //l1->next->next = new ListNode(3);
    ListNode* l2 = new ListNode(1);
    l2->next = new ListNode(2);
    l2->next->next = new ListNode(3);
    ListNode* l3;
    l3= addTwoNumber(l1, l2);
    cout << l3->next->next->val << l3->next->val << l3->val;
   */
}
ListNode* addTwoNumber(ListNode* l1, ListNode* l2)
{
    ListNode* headptr = new ListNode(0);
    ListNode* node = new ListNode(0);
    headptr = node;        //定义一个头指针
    int carry=0,sum=0;     //carry用于保存进位，sum%10用于存放每一位的数

    while (l1 != nullptr && l2 != nullptr)
    {
        sum = carry + l1->val + l2->val;
        if (sum / 10)
        {
            carry = 1;
        }
        else
        {
            carry = 0;
        }
        node->val = sum % 10;
        node->next = new ListNode(0);
        node = node->next;
        l1 = l1->next;
        l2 = l2->next;
    }
      
    if (l1 == nullptr && l2 == nullptr)
    {
        if (carry)
        {
            node->next = new ListNode(0);
            node = node->next;
            node->val = 1;
        }
        return headptr;
    }


    while (l1 != nullptr)
    {
       
        sum = carry + l1->val;
        if (sum / 10)
        {
            carry = 1;
        }
        else
        {
            carry = 0;
        }
        node->val = sum % 10;
        l1 = l1->next;
        node->next = new ListNode(0);
        node = node->next;
    }
   
    while (l2 != nullptr)
    {
        sum = carry + l2->val;
        if (sum / 10)
        {
            carry = 1;
        }
        else
        {
            carry = 0;
        }
        node->val = sum % 10;
        l2 = l2->next;
        node->next = new ListNode(0);
        node = node->next;
    }
    if (carry == 1)
    {
        node->next = new ListNode(0);
        node = node->next;
        node->val = 1;
        return headptr;
    }
    return headptr;
}
