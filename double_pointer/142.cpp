//
// Created by skyyw on 2022/1/22.
//
#include <unordered_set>
using namespace std;
struct ListNode {
    int val;
    ListNode * next;
    ListNode(int x) : val(x),next(nullptr){}
};
class Solution {
public:
    //哈希表
    ListNode *detectCycle(ListNode *head) {
    unordered_set<ListNode *>set;
    while(head!= nullptr){
        if(set.count(head)){
            return head;
        }
        set.insert(head);
        head=head->next;
    }
        return nullptr;
    }
    //Floyd判圈
    ListNode *detectCycle2(ListNode *head){
    ListNode *slow=head,*fast=head;
    while(fast!= nullptr){
        slow=slow->next;
        if(fast->next== nullptr) return nullptr;
        fast=fast->next->next;
        if(fast==slow){
            ListNode * ptr = head;
            while(ptr!=slow){
                ptr=ptr->next;
                slow=slow->next;
            }
            return ptr;
        }
        }
        return nullptr;
    }
};