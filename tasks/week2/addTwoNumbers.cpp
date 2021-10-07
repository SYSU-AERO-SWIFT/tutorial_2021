ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
{
	ListNode *temp1=l1,*temp2=l2;//设置遍历链表的指针
	ListNode *result=NULL;//结果
	ListNode *temp3=result;//用于插入
	int reg=0,temp=0;//reg为进位，temp为当前位置存入数据
	while(temp1!=NULL&&temp2!=NULL)
	{
		if(temp1==NULL)
		{
			temp=temp2->val+reg;
			temp2=temp2->next;
		}
		else if(temp2==NULL)
		{
			temp=temp1->val+reg;
			temp1=temp1->next;
		}
		else
		{
			temp=temp1->val+temp2->val+reg;
			temp1=temp1->next;
			temp2=temp2->next;
		}
		reg=temp/10;
		temp%=10;
		ListNode* insert=new ListNode(temp);
		if(result==NULL)
		{
			result=insert;
			temp3=result;
		}
		else
		{
			temp3->next=insert;
			temp3=temp3->next;
		}
	}
	if(reg!=0)
	{
		ListNode* insert=new ListNode(temp);
		temp3->next=insert;
	}
	return result;
}
