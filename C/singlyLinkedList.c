// imports libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//definition of a node for a singly linked list
typedef struct node {
    int data;
    struct node* next;
}
node;
/**
IGNORE COMMENTS!!!
*/
// prototypes of functions, easy reference for parameters and return dataues
// prints the data of all nodes of list
void printList(node* list);
// appends a node to the end of the list
node* appendNode(node *list, int data);
// allocates memory for a new node (used within functions)
node* allocNode(node *list);
// inserts node before a specified data within list
node* insertNodeBefore(node *list, int data, int nextData);
// prepends a node to the start of the list
node* prependNode(node *list, int data);
// inserts a node after a specified data within the linked list
node* insertNodeAfter(node *list, int data, int nextData);
// deletes a node from the list
node* removeNode(node* list, int data);
// returns middle node of the list
node* middleList(node* list);
// reverses the entire linked list example: [1,2,3] -> [3,2,1]
node* reverseList(node *list);
// deletes middle node and returns head of new list
node* deleteMiddle(node* list);
// sorts a given linked list using bubble sort
node* sortList(node* list);

int main(void) {
    // node datad 'list' is initialized as the head, wtih data
    node* list = appendNode(NULL, 3);
    // 6 node is added
    appendNode(list, 6);
    // 0 node is added
    appendNode(list, 0);
    // 34 node is appended as the head of the list
    appendNode(list, 34);
    // prints current list nodes in order
    printList(list);
    // sorts current list from least to greatest
    sortList(list);
    // prints new list in order
    printList(list);
}
/**
 * @brief allocates memory for a node, checks if memory is available
 * @param list head of the list used to free the list if there is no memory available
 * @return node* returns empty node
 */
node* allocNode(node* list) {
    node *n = malloc(sizeof(node));
    if(n == NULL) {
        node *tmp = list->next;
        while(list != NULL) {
            tmp = list->next;
            free(list);
            list = tmp;
        }
    }
    return n;
}
/**
 * @brief adds node to the end of a list
 * 
 * @param list used for allocNode() to create a new node, used to traverse list and append a node to the tail
 * @param data used to assign a data dataue to the new node
 * @return node* returns the new completed node
 */
node* appendNode(node* list, int data) {
    node *n = allocNode(list);
    if(n != NULL) {
        n->data = data;
        n->next = NULL;
        if (list==NULL) {
            return n;
        }
        while(list->next != NULL) {
            list = list->next;
        }
        // list is tail now
        list->next = n;
    }
    return n;
}
/**
 * @brief inserts a node before the node with the provided data
 * 
 * @param list used to traverse list through head
 * @param data data of node to be inserted
 * @param nextData data of node to come after new node
 * @return node*
 */
node* insertNodeBefore(node* list, int data, int nextData) {
    node* n = allocNode(list);
    if(n != NULL) {
        n->data = data;
        n->next = NULL;
        //n->next = list->next;
        if (list->next==NULL) {
            return n;
        }
        while(list->next->data != nextData) {
            list = list->next;
            if (list->next ==NULL) {
                printf("Warning: %s not found for insertion before\n", nextData);
                return NULL;
            }
        }
        n->next = list->next;
        list->next = n;
    }
    return n;
}
/**
 * @brief inserts node after given data
 * 
 * @param list used to traverse list 
 * @param data datat of new node to be inserted
 * @param beforeData data of node that will be right before new node
 * @return node* 
 */
node* insertNodeAfter(node* list, int data, int beforeData) {
    node* n = allocNode(list);
    if(n != NULL) {
        n->data = data;
        n->next = NULL;
        if (list->next==NULL) {
            return n;
        }
        while(list->next->data != beforeData) {
            list = list->next;
            if (list->next == NULL) {
                printf("Warning: %s not found for insertion \n", beforeData);
                return NULL;
            }
        }
        n->next = list->next->next->next;
        list->next->next = n;
    }
    return n;
}
/**
 * @brief creates a new head of the list
 * 
 * @param list used to prepend node before the head
 * @param data data of new node
 * @return node* 
 */
node* prependNode(node* list, int data){
    node *n = allocNode(list);
    n->next = list;
    list = n;
    list->data = data;
    return list;
}
/**
 * @brief reverses entire list 
 * 
 * @param list used to traverse list
 * @return node* returned in order to set new head
 */
node* reverseList(node* list) {
    node* previous = allocNode(list);
    node* next = allocNode(list);
    previous = NULL;
    for(node* current = list;current != NULL;current = next){
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    list = previous;
    return list;
}
/**
 * @brief deletes a node from list
 * 
 * @param list used to traverse node
 * @param data used to identify node to be deleted
 * @return node* 
 */
node* removeNode(node* list, int data) {
    node* delete = list;
    node* previous = allocNode(list);
    if (delete != NULL && delete->data == data) {
        list = delete->next; // Changed head
        free(delete); // free old head
        return list;
    }
    while (delete->data != data) {
        previous = delete;
        delete = delete->next;
    }
    previous->next = delete->next;
    return list;
}
/**
 * @brief prints list using loop
 * @param list used to traverse each node, starts from head
 */
void printList(node* list) {
    for(node* current = list;current != NULL;current = current->next) {
        printf("%i\n", current->data );
    }
    printf("\n");
    return;
}
/**
 * @brief two pointers traverse list one at double speed
 * 
 * @param list original list to be traversed
 * @return node* final tmp dataue returned as middle
 */
node* middleList(node* list) {
    node* tmp = list;
    for(; list != NULL && list->next !=NULL; list = list->next->next) {
         tmp = tmp->next; 
    }
    return tmp;
}
/**
 * @brief deletes middle node and returns new list
 * 
 * @param list list that needs middle deleted
 * @return node* head of the list
 */
node* deleteMiddle(node* list){
    node* mid = list;
    node* fast = list;
    node* prev = NULL;
    if(list->next == NULL){
        return prev;
    }
    else if(list->next->next == NULL) {
        list->next = NULL;
        return list;
    }
    while(fast && fast->next) {
        prev = mid;
        mid = mid->next;
        fast = fast->next->next;
    }
    prev->next = prev->next->next;
    return list;
}
/**
 * @brief sorts nodes in list from least to greatest data, returns new list
 * 
 * @param list to be sorted
 * @return node* head of new sorted list
 */
node* sortList(node* list){
    if(list == NULL || list->next == NULL) {
       return list;
    }
    node* current = list;
    node* nxt = current->next;
    node* p = list;
    int count = 0;
    int len = 0;
    int buffer;
    while(p->next) {
        p = p->next;
        len++;
    }
    while(count < len) {
        for(int i = 0; i < len; i++) {
            if(current->data > nxt->data) {
                buffer = current->data;
                current->data = nxt->data;
                nxt->data = buffer;
            }
            if(current->next && nxt->next) {
                current = current->next;
                nxt = nxt->next;
            }
        }
        current = list;
        nxt = list->next;
        count++;
    }
    return list;
}
