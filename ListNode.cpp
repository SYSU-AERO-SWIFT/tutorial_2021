 struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
   
};

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        ListNode* result = new ListNode(0);//新链表
        ListNode* tmp = result;//相加运算用的指针
        int sum = 0;
        while (l1 || l2) {
            if (l1) {
                sum += l1->val;
                l1 = l1->next;
            }
            if (l2) {
                sum += l2->val;
                l2 = l2->next;//这俩是不一样长的时候，没说就直接取有值的那个了
            }
            tmp->next = new ListNode(sum % 10);//尾数
            sum /= 10;//进位
            tmp = tmp->next;//
        }
        if (sum)
            tmp->next = new ListNode(1);//延长
        return result->next;
    }

int main(){return 0;}
