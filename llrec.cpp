#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

// must be recursive
void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot) {
    // base condition: reach end of list
    if (head == NULL) {
        return;
    }

    // saving next node and isolate current node from list
    Node *next = head->next;
    head->next = NULL;

    if (head->val <= pivot) {
        smaller = head;
        llpivot(next, smaller->next, larger, pivot);
    } else {
        larger = head;
        llpivot(next, smaller, larger->next, pivot);
    }
}


