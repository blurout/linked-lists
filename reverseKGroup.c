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

// functions above main() are the 'main' functions
/**
 * @brief Get's the Kth Node object
 * 
 * @param curr current node in the group
 * @param k the length of the group
 * @return struct ListNode* returns the end/kth node of the given group
 */
struct ListNode* getKthNode(struct ListNode* curr, int k) {
    //iterrates through the list while, looking to end on the kth node
    while(curr && k > 0) {
        curr = curr->next;
        k--;
    }
    // returns kth node
    return curr;
}

/**
 * @brief 
 * 
 * @param head 
 * @param k 
 * @return struct ListNode* 
 */
struct ListNode* reverseKGroup(struct ListNode* head, int k) {
    struct ListNode* dummyNode;
    struct ListNode* groupPrev;
    struct ListNode* groupNext;
    struct ListNode* KthNode;
    struct ListNode* tmp;
    // nodes for reversing group
    struct ListNode* curr;
    struct ListNode* prev;
    struct ListNode* placeHolder;
    
    dummyNode->val = 0;
    dummyNode->next = head;
    groupPrev = dummyNode;
    
    while (true) {
        KthNode = getKthNode(groupPrev, k);
        if (KthNode == NULL) {
            break;
        }
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
        
        tmp = groupPrev->next;
        groupPrev->next = KthNode;
        groupPrev = tmp; 
    }
    return dummyNode->next;
}

int main(void) {
    ListNode* head = appendNode(NULL, 1);
    appendNode(head, 2);
    appendNode(head, 3);
        for(ListNode* tmp = head;tmp; tmp=tmp->next) {
        printf("%i\n", tmp->val);
    }
    head = reverseKGroup(head, 2);
    printf("\n");
    for(ListNode* tmp = head;tmp; tmp=tmp->next) {
        printf("%i\n", tmp->val);
    }

}

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
ListNode* appendNode(ListNode* head, int data) {
    ListNode *n = allocNode(head);
    if(n != NULL) {
        n->val = data;
        n->next = NULL;
        if (head==NULL) {
            return n;
        }
        while(head->next != NULL) {
            head = head->next;
        }
        // list is tail now
        head->next = n;
    }
    return n;
}