#include <iostream>
#include <vector>
using namespace std;

class ListNode {
    public:
    int val;
    ListNode* next;

    ListNode(){

    }

    ListNode(int val) {
        this->val = val;
    }

    ListNode(int val, ListNode* next) {
        this->val = val;
        this->next = next;
    }
};

// QUESTION 1
// TO REVERSE A LINKED LIST LEETCODE
ListNode* reverseList(ListNode* head) {

    if(head == nullptr || head->next == nullptr)
        return head;

    ListNode* prev = nullptr;
    ListNode* curr = head;

    while(curr != nullptr) {
        ListNode* currnew = curr->next;
        curr->next = prev;
        prev = curr;
        curr = currnew;
    }

    return prev;
}

// QUESTION 2
// TO MERGE TWO LINKED LISTS LEETCODE
ListNode* mergeTwoLists(ListNode* A, ListNode* B) {
    if(A == nullptr)
        return B;
    else if(B == nullptr)
        return A;
    
    ListNode* head = new ListNode(-1);
    ListNode* curr = head;

    while(A != nullptr && B != nullptr) {
        if(A->val <= B->val) {
            curr->next = A;
            curr = A;
            A = A->next;
        }

        else{
            curr->next = B;
            curr = B;
            B = B->next;
        }
    }

    if(A != nullptr) 
        curr->next = A;
    else if(B != nullptr) 
        curr->next = B;
    
    return head->next;
}

// QUESTION 3
// TO FIND MIDDLE OF THE LINKED LIST LEETCODE
ListNode* middleOfList(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    while(fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

// QUESTION 4
// TO FIND MIDDLE OF THE LINKED LIST VARIATION LEETCODE
ListNode* middleNode(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    while(fast != nullptr && fast->next != nullptr && fast->next->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

// QUESTION 5
// TO SORT A LINKED LIST LEETCODE
// HERE WE ARE USING MERGE SORT
ListNode* sortList(ListNode* head) {
    if(head == nullptr || head->next == nullptr)
        return head;
    
    ListNode* mid = middleNode(head);
    ListNode* newHead = mid->next;
    mid->next = nullptr;

    return mergeTwoLists(sortList(head), sortList(newHead));
}

// QUESTION 6
// TO MERGE K SORTED LISTS LEETCODE
ListNode* mergeKLists_(vector<ListNode*> lists, int si, int ei) {
    if(si == ei)
        return lists[si];
    if(si + 1 == ei)
        return mergeTwoLists(lists[si], lists[ei]);
    
    int mid = (si + ei) >> 1;
    ListNode* left = mergeKLists_(lists, si, mid);
    ListNode* right = mergeKLists_(lists, mid + 1, ei);

    return mergeTwoLists(left, right);
}

ListNode* mergeKLists(vector<ListNode*> lists) {
    if(lists.size() == 0) 
        return nullptr;
    return mergeKLists_(lists, 0, lists.size() - 1);
}

int main(int argc, char** argv) {

}