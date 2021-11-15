#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
{
	int num1, num2, i, j;
	num1 = num2 = i = j = 0;
	for (ListNode* p = l1; p != NULL; p = p->next)
	{
		num1 += pow(10, i) * p->val;
		i++;
	}
	for (ListNode* p = l2; p != NULL; p = p->next)
	{
		num2 += pow(10, j) * p->val;
		j++;
	}
	if (num1/num2 < 1 || num1/num2 > 9)
		return NULL;
	int sum = num1 + num2;
	//cout << "create node(" << sum%10 << ")" << endl;
	
	ListNode node = ListNode(sum % 10);
	ListNode newNode = ListNode(0);
	
	ListNode* ptr = &node;
	sum /= 10;
	cout << "p -> val = " << ptr->val << endl;
	while (sum > 0)
	{
		ptr->next = new ListNode(sum%10);
		//cout << "create node(" << sum%10 << ")" << endl;
		ptr = ptr->next;
		
		cout << "p -> val = " << ptr->val << endl;
		sum /= 10;
	}
	ptr = NULL;
//	for (ListNode* p = &node; p != NULL; p = p->next)
//	{
//		cout << p->val << " ";
//	}
//	cout << endl;
	ListNode* head = &node;
	return head;
}

int main()
{
	//链表1 
	ListNode Node1 = ListNode(7);
	ListNode Node2 = ListNode(1);
	ListNode Node3 = ListNode(6);
	Node1.next = &Node2;
	Node2.next = &Node3;
	Node3.next = NULL;
	//链表2 
	ListNode Node4 = ListNode(5);
	ListNode Node5 = ListNode(9);
	ListNode Node6 = ListNode(2);
	Node4.next = &Node5;
	Node5.next = &Node6;
	Node6.next = NULL;
	//链表求和并测试 
	ListNode* p = addTwoNumbers(&Node1, &Node4);
	cout << p->val << " -> " ;
	cout << p->next->val;
	//cout << " -> " << p->next->next->val << endl;
	return 0;
}
