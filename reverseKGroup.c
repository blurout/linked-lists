//standard libraries for operations
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// singly linked list def
typedef struct ListNode {
     int val;
     struct ListNode *next;
}
ListNode;

// headers for the boring functions
ListNode* allocNode(ListNode* head);
ListNode* appendNode(ListNode* head, int data);
void printLinkedList(ListNode* head);
// functions above main() are the 'main' functions
/**
 * @brief Get's the Kth Node object
 * 
 * @param curr current node in the group
 * @param k the length of the group
 * @return struct ListNode* returns the end/kth node of the given group
 */
struct ListNode* getKthNode(struct ListNode* curr, int k) {
    //iterrates through the list while current node is not NULL; looking to end on the kth node
    while(curr && k > 0) {
        curr = curr->next;
        k--;
    }
    // returns kth node
    return curr;
}

/**
 * @brief  reverses K nodes at a time and returns final list
 * 
 * @param head the head of a linked list
 * @param k the number of nodes to be reversed in each group (ex: reverse 3 nodes at a times)
 * @return struct ListNode* returns final list
 */
// side note: function leaves remaining nodes that do not match the group size, as is
struct ListNode* reverseKGroup(struct ListNode* head, int k) {
    // used to start the grouping and store the head value
    struct ListNode* dummyNode;
    // holds the previous node before group
    struct ListNode* groupPrev;
    // holds the next node after the group
    struct ListNode* groupNext;
    // holds the kth node in the group
    struct ListNode* KthNode;
    // holds previous node; links reversed group back to list
    struct ListNode* tmp;
    // nodes for reversing group
    struct ListNode* curr;
    struct ListNode* prev;
    struct ListNode* placeHolder;
    
    // dummy node initialized
    dummyNode->val = 0;
    dummyNode->next = head;
    groupPrev = dummyNode;
    
    // begins looping through list
    while (true) {
        // initializes kth node
        KthNode = getKthNode(groupPrev, k);
        // checks if kth node is NULL (usually when no more whole groups left)
        if (KthNode == NULL) {
            break;
        }
        // intializes the head of the next group
        groupNext = KthNode->next;
        
        // reversing group
        prev = KthNode->next;
        curr = groupPrev->next;
        while (curr != groupNext) {
            placeHolder = curr->next;
            curr->next = prev;
            prev = curr;
            curr = placeHolder;
        }
        
        // temporarilly holds tail of reversed group (old head of group)
        tmp = groupPrev->next;
        // sets new dummy node for next group
        groupPrev->next = KthNode;
        // old groups new tail assigned as new previous node
        groupPrev = tmp; 
    }
    // returns head of list
    return dummyNode->next;
}

// main begins
int main(void) {
    // linked list initialized; node 0
    ListNode* head = appendNode(NULL, 1);
    // node 1
    appendNode(head, 2);
    // node 2
    appendNode(head, 3);
    // prints current list
    printLinkedList(head);
    // reverses each set of k nodes 
    head = reverseKGroup(head, 2);
    // prints new list
    printLinkedList(head);
}
// main ends

/**
 * @brief allocates space for new node to be appended
 * 
 * @param head takes in list as a parameter in case it needs to be freed
 * @return ListNode* returns newly allocated node to caller
 */
ListNode* allocNode(ListNode* head) {
    ListNode *n = malloc(sizeof(ListNode));
    if(n == NULL) {
        ListNode *tmp = head->next;
        while(head != NULL) {
            tmp = head->next;
            free(head);
            head = tmp;
        }
    }
    return n;
}
/**
 * @brief appends nodes to list
 * 
 * @param head head of list to be added to
 * @param data data to be initialized in node
 * @return ListNode* returns newly appended node
 */
ListNode* appendNode(ListNode* head, int data) {
    ListNode *n = allocNode(head);
    if(n) {
        n->val = data;
        n->next = NULL;
        if (head == NULL) {
            return n;
        }
        while(head->next) {
            head = head->next;
        }
        // list is tail now
        head->next = n;
    }
    return n;
}
/**
 * @brief prints linked list
 * 
 * @param head of linked list to be printed
 */
void printLinkedList(ListNode* head) {
    for(ListNode* tmp = head;tmp; tmp=tmp->next) {
        printf("%i\n", tmp->val);
    }
    printf("\n");

}