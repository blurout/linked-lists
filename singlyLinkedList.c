// imports libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


//definition of a node for a singly linked list
typedef struct node {
    char* name;
    struct node* next;
}
node;


// prototypes of functions, easy reference for parameters and return values
// prints the data of all nodes of list
void printList(node* list);
// appends a node to the end of the list
node* appendNode(node *list, char* data);
// allocates memory for a new node (used within functions)
node* allocNode(node *list);
// inserts node before a specified data within list
node* insertNodeBefore(node *list, char* data, char* nextData);
// prepends a node to the start of the list
node* prependNode(node *list, char* data);
// inserts a node after a specified data within the linked list
node* insertNodeAfter(node *list, char* data, char* nextData);
// reverses entire linked list example: [1]->[2]->[3] = [3]->[2]->[1]
node* reverseList(node *list);
// deletes a node from the list
node* removeNode(node* list, char* data);

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
    // node named 'list' is initialized as the head, wtih data "Banana"
    node* list = appendNode(NULL,"Banana");
    // "Cantaloupe" node is added
    appendNode(list,"Cantaloupe");
    // "Dragon Fruit" node is added
    appendNode(list,"Dragon Fruit");
    // "Fig" node is added
    appendNode(list,"Fig");
    // "Elderberry" node is inserted before "Fig"
    insertNodeBefore(list,"Elderberry", "Fig");
    // "Blueberry" node is inserted before "Cantaloupe"
    insertNodeBefore(list,"Blueberry", "Cantaloupe");
    // "Cherry" node is inserted before "Cantaloupe"
    insertNodeAfter(list, "Cherry", "Cantaloupe");
    // prepends node with data "Apple" to the list, "Apple" node becomes head
    list = prependNode(list, "Apple");
    // prints all the data in the list
    printList(list);
    // reverses all the pointers of the current list
    list = reverseList(list);
    // prints all the data in the list
    printList(list);
    // removes node with the data "Fig" from list
    list = removeNode(list, "Fig");
    // prints all the data in the list
    printList(list);

    // finding and returning the middle of a singly linked list
    // 4 algorithms
    
    // nums nodes to be appended to list (to calculate time complexity)
    const int NUMNODES = 15000;
    // middle is predetermined to check
    const int MYMIDDLE = NUMNODES/2;
    // appends NUMNODES number of nodes list above
    for(int i = 0; i <= NUMNODES; i++) {
        // allocates memory for current addition of node
        char* istr = malloc(sizeof(char*));
        // appends the new node to the list
        // itoa is used here to convert the current iteration number as a string to be used as the nodes data
        appendNode(list, itoa (i,istr,10));
    }
    


    // intializes the clock variable
    clock_t t;
    // sets a double to hold number of seconds starting from 0
    double time_taken = 0;
    // first algorithm middleEven
    // starts clocking
    t = clock();
    // calls middleEven, assigns returned value to str
    char* str = middleEven(list)->name;
    // subtracts clocks in 't' from current number of clocks, gives true number of clocks. assigns time_taken to seconds converted from clocks
    time_taken = ((double) (clock() - t))/CLOCKS_PER_SEC; // in seconds
    // prints time and result
    printf("Time MiddleEven %f  returns: %s\n", time_taken, str);
 
    // second algorithm middleSlow (slowest)
    // sets current number of clocks as the new start clock count
    t = clock();
    // calls the algorithm middleSlow and assigns the returned value to str
    str = middleSlow(list)->name;
    // subtracts clocks in 't' from current number of clocks, gives true number of clocks. assigns time_taken to seconds converted from clocks
    time_taken = ((double) (clock() - t))/CLOCKS_PER_SEC; // in seconds
    // prints time and result
    printf("Time MiddleSlow %f  returns: %s\n", time_taken, str);
    
    // third algo (fastest)
    // sets current number of clocks as the new start clock count
    t = clock();
    // calls middleZipZip, assigns returned value to str
    str = middleZipZip(list)->name;
    // subtracts clocks in 't' from current number of clocks, gives true number of clocks. assigns time_taken to seconds converted from clocks
    time_taken = ((double) (clock() - t))/CLOCKS_PER_SEC; // in seconds
    // prints time and result
    printf("Time MiddleZipZip %f  returns: %s\n", time_taken, str);
    
    // fourth algo (true fastest, but predetermined)
    // sets current number of clocks as the new start clock count
    t = clock();
    // calls middelCounter, assigns returned value to str
    str = middleCounter(list, MYMIDDLE)->name;
    // subtracts clocks in 't' from current number of clocks, gives true number of clocks. assigns time_taken to seconds converted from clocks
    time_taken = ((double) (clock() - t))/CLOCKS_PER_SEC; // in seconds
    // prints time and result
    printf("Time MiddleCounter %f  returns: %s\n", time_taken, str);
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
node* appendNode(node* list, char* data) {
    node *n = allocNode(list);
    if(n != NULL) {
        n->name = data;
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
node* insertNodeBefore(node* list, char* data, char* nextData) {
    node* n = allocNode(list);
    if(n != NULL) {
        n->name = data;
        n->next = NULL;
        //n->next = list->next;
        if (list->next==NULL) {
            return n;
        }
        while(list->next->name != nextData) {
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
node* insertNodeAfter(node* list, char* data, char* beforeData) {
    node* n = allocNode(list);
    if(n != NULL) {
        n->name = data;
        n->next = NULL;
        if (list->next==NULL) {
            return n;
        }
        while(list->next->name != beforeData) {
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
node* prependNode(node* list, char* data){
    node *n = allocNode(list);
    n->next = list;
    list = n;
    list->name = data;
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
node* removeNode(node* list, char* data) {
    node* delete = list;
    node* previous = allocNode(list);
    if (delete != NULL && delete->name == data) {
        list = delete->next; // Changed head
        free(delete); // free old head
        return list;
    }
    while (delete->name != data) {
        previous = delete;
        delete = delete->next;
    }
    previous->next = delete->next;
    return list;
}
/**
 * @brief prints list using loop
 * 
 * @param list used to traverse each node
 */
void printList(node* list) {
    for(node* current = list;current != NULL;current = current->next) {
        printf("%s\n", current->name );
    }
    printf("\n");
    return;
}
/**
 * @brief next four algorithms find middle and return middle node
 * 
 * @param list 
 * @return node* 
 */
node* middleEven(node* list) {
    int count = 0;
    node* tmp = list;
    for(; list != NULL; list = list->next) {
        if(count % 2 != 0) {
            tmp = tmp->next; 
        }
        count++;
       // mid = tmp;
    }
    return tmp;
}
node* middleCounter(node* list, int MYMIDDLE) {
    int count = 0;
    node* mid;
    int mymiddle = MYMIDDLE;
    for(node* tmp = list; mymiddle--; list = list->next) {
    }
    return list;
}
node* middleZipZip(node* list) {
    int count = 0;
    node* tmp = list;
    for(; list != NULL && list->next !=NULL; list = list->next->next) {
         tmp = tmp->next; 
    }
    return tmp;
}
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
