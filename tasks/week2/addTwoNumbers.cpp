ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
{
	ListNode *temp1=l1,*temp2=l2;//���ñ��������ָ��
	ListNode *result=NULL;//���
	ListNode *temp3=result;//���ڲ���
	int reg=0,temp=0;//regΪ��λ��tempΪ��ǰλ�ô�������
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
