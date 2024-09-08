 struct ListNode {
     int val;
     ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };

// ... -> A -> B -> C

#define NODEA cur
#define NODEB cur->next
#define NODEC cur->next->next

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode *a, *b, *c, *prev;
        if (!head || !head->next)
        {
            return head;
        }
        // first swap is outside the loop to replace head
        a = head;
        b = head->next;
        c = head->next->next;
        head = b;
        b->next = a;
        a->next = c;
        while (c && c->next)
        {
            prev = a;
            a = c;
            b = c->next;
            c = c->next->next;
            //
            prev->next = b;
            b->next = a;
            a->next = c;
        }
        return head;
    }
};


int main(int argc, char **argv)
{
    ListNode d = {4};
    ListNode c = {3, &d};
    ListNode b = {2, &c};
    ListNode a = {1, &b};
    auto s = Solution();
    s.swapPairs(&a);
    return 0;
}