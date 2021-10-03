#include <iostream> 
using namespace std; 

struct ListNode{
	int val; 
	ListNode *next; 
	ListNode(int x):val(x),next(NULL) {}
}

ListNode* addTwoNumbers(ListNode* l1,ListNode* l2){
	//memory leak danger
	ListNode* head = new ListNode(0); 
        ListNode* now  = head; 

	

	return &head; 
}
