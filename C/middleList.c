// imports important libraries used throughout 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//definition of a node for a singly linked list, as a data and a pointer to the next node
typedef struct node {
    int data;
    struct node* next;
}
node;

// appends or adds a node to the end of the linked list
node* appendNode(node *list, int data);
// allocates memory for a new node (used within functions)
node* allocNode(node *list);
// start of methods that find and return the middle node of a linked list
// updates return node when the counter is odd, when the loop reaches null, the tmp node had only traversed half of the list
node* middleEven(node* list);
// gets length of list, divides length by 2, traverses list until new length is reached, returns node it finishes on
node* middleSlow(node* list);
// duplicates list, original list is traversed two nodes at a time, duplicate list one node at a time. 
// original reaches null, duplicate reaches middle and returns the current node
node* middleZipZip(node* list);
// middle length, list is traversed determined number of times, returns end node
node* middleCounter(node* list, int MYMIDDLE);

int main(void) {
    // finding and returning the middle of a singly linked list
    // 4 algorithms
    node* list = appendNode(NULL, 1);
    // nums nodes to be appended to list (to calculate time complexity)
    const int NUMNODES = 5000;
    // middle is predetermined to check
    const int MYMIDDLE = NUMNODES/2;
    // appends NUMNODES number of nodes list above
    for(int i = 0; i <= NUMNODES; i++) {
        // appends the new node to the list
        appendNode(list, i);
    }

    // intializes the clock variable
    clock_t t;
    // sets a double to hold number of seconds starting from 0
    double time_taken = 0;

    // first algorithm middleEven
    // starts clocking
    t = clock();
    // calls middleEven, assigns returned value to midnum
    int midnum = middleEven(list)->data;
    // subtracts clocks in 't' from current number of clocks, gives true number of clocks. assigns time_taken to seconds converted from clocks
    time_taken = ((double) (clock() - t))/CLOCKS_PER_SEC; // in seconds
    // prints time and result
    printf("Time MiddleEven %f  returns: %i\n", time_taken, midnum);
 
    // second algorithm middleSlow (slowest)
    // sets current number of clocks as the new start clock count
    t = clock();
    // calls the algorithm middleSlow and assigns the returned value to midnum
    midnum = middleSlow(list)->data;
    // subtracts clocks in 't' from current number of clocks, gives true number of clocks. assigns time_taken to seconds converted from clocks
    time_taken = ((double) (clock() - t))/CLOCKS_PER_SEC; // in seconds
    // prints time and result
    printf("Time MiddleSlow %f  returns: %i\n", time_taken, midnum);
    
    // third algo (fastest)
    // sets current number of clocks as the new start clock count
    t = clock();
    // calls middleZipZip, assigns returned value to midnum
    midnum = middleZipZip(list)->data;
    // subtracts clocks in 't' from current number of clocks, gives true number of clocks. assigns time_taken to seconds converted from clocks
    time_taken = ((double) (clock() - t))/CLOCKS_PER_SEC; // in seconds
    // prints time and result
    printf("Time MiddleZipZip %f  returns: %i\n", time_taken, midnum);
    
    // fourth algo (true fastest, but predetermined)
    // sets current number of clocks as the new start clock count
    t = clock();
    // calls middelCounter, assigns returned value to midnum
    midnum = middleCounter(list, MYMIDDLE)->data;
    // subtracts clocks in 't' from current number of clocks, gives true number of clocks. assigns time_taken to seconds converted from clocks
    time_taken = ((double) (clock() - t))/CLOCKS_PER_SEC; // in seconds
    // prints time and result
    printf("Time MiddleCounter %f  returns: %i\n", time_taken, midnum);
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
 * @param data used to assign a data value to the new node
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

// next four algorithms find middle and return middle node
/**
 * @brief finds and returns middle node
 * 
 * @param list used to traverse list
 * @return node* the middle node that is returned
 */
node* middleEven(node* list) {
    int count = 0;
    // duplicates head
    node* tmp = list;
    // traverses list ever iteration, tmp is re assigned only on odd counts
    for(; list != NULL; list = list->next) {
        if(count % 2 != 0) {
            tmp = tmp->next; 
        }
        count++;
       // mid = tmp;
    }
    // list reaches NULL while tmp reaches middle
    return tmp;
}
/**
 * @brief traverses list only predefined number of times
 * 
 * @param list list to be iterated through
 * @param MYMIDDLE predetermined halfway point
 * @return node* returns end node
 */
node* middleCounter(node* list, int MYMIDDLE) {
    int count = 0;
    node* mid;
    int mymiddle = MYMIDDLE;
    for(node* tmp = list; mymiddle--; list = list->next) {
    }
    return list;
}
/**
 * @brief two pointers traverse list one at double speed
 * 
 * @param list original list to be traversed
 * @return node* final tmp value returned as middle
 */
node* middleZipZip(node* list) {
    int count = 0;
    node* tmp = list;
    for(; list != NULL && list->next !=NULL; list = list->next->next) {
         tmp = tmp->next; 
    }
    return tmp;
}
/**
 * @brief counts the length of list then traverses list again until half count is reached
 * 
 * @param list original list
 * @return node* returns middle node
 */
node* middleSlow(node* list) {
    int count = 0;
    node* tmp = list;
    while(tmp != NULL) {
        tmp = tmp->next;
        count++;
    }
    count /= 2;
    for(int i = 0;i < count;i++){
        list = list->next;
    }
    return list;
}
