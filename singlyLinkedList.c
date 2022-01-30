// imports important libraries used throughout 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//definition of a node for a singly linked list, as a name and a pointer to the next node
typedef struct node {
    char* name;
    struct node* next;
}
node;

// prototypes of functions, easy reference for parameters and what each function does
// prints all nodes specifically the name in list with a line in between each node
void printList(node* list);
// appends or adds a node to the end of the linked list
node* appendNode(node *list, char* data);
// allocates memory for a new node (used within functions)
node* allocNode(node *list);
// allows insertion of a node before a specified value within the linked list
node* insertNodeBefore(node *list, char* data, char* nextData);
// prepends or inserts a node to the start of the list
node* prependNode(node *list, char* data);
// allows insertion of a node after a specified value within the linked list
node* insertNodeAfter(node *list, char* data, char* nextData);
// reverses the entire linked list example: [1]->[2]->[3] => [3]->[2]->[1]
node* reverseList(node *list);
// deletes a node from the linked list
node* removeNode(node* list, char* data);

// start of methods that find and return the middle of a linked list

// finds the middle node by only updating the return node when the counter is odd, when the loop reaches null, the tmp node had only traversed half of the list
node* middleEven(node* list);
// counts the length of the list, divides the length by 2, traverses for only half length of the list, returns node it finishes on
node* middleSlow(node* list);
// original list is duplicated, the original list is traversed two nodes at a time, duplicate list one node at a time. 
// once the original reaches null the duplicate reaches the middle and returns the current node
node* middleZipZip(node* list);
// given a predermined length and middle length, list is traversed determined number of times and returns current node at the end of loop
node* middleCounter(node* list, int MYMIDDLE);

int main(void) {
    // list named 'list' is initialized with a head string "Banana"
    node* list = appendNode(NULL,"Banana");
    // "Cantaloupe" is added to the end of the list
    appendNode(list,"Cantaloupe");
    // "Dragon Fruit" is added to the end of the list
    appendNode(list,"Dragon Fruit");
    // "Fig" is added to the end of the list
    appendNode(list,"Fig");
    // "Elderberry" is inserted before "Fig"
    insertNodeBefore(list,"Elderberry", "Fig");
    // "Blueberry" is inserted before "Cantaloupe"
    insertNodeBefore(list,"Blueberry", "Cantaloupe");
    // "Cherry" is inserted before "Cantaloupe"
    insertNodeAfter(list, "Cherry", "Cantaloupe");
    // prepends "Apple" to the lsit, "list" or the head of the list is assigned to a new node, whose data is "Apple", whose next is node points to previous head
    list = prependNode(list, "Apple");
    // prints all the nodes in the list
    printList(list);
    // reverses all the pointers of the current list and reassigns the tail to the head
    list = reverseList(list);
    // prints all the nodes of the newly reversed list
    printList(list);
    // removes the node with the data "Fig" from the linked list
    list = removeNode(list, "Fig");
    // prints the list again
    printList(list);

    // finding and returning the middle of a singly linked list
    // 4 algorithms
    
    // sets the amount of nodes to be appended to the list to better calculate time complexity
    const int NUMNODES = 15000;
    // middle is predetermined to confirm correctness
    const int MYMIDDLE = NUMNODES/2;
    // appends NUMNODES number of nodes to the original list above
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
    // calls the algorithm middleEven and assigns the returned value to str
    char* str = middleEven(list)->name;
    // subtracts the number of clocks stored in 't' from the current number of clocks, giving us the true number of clocks. converts clocks to seconds and assigns it to time_taken
    time_taken = ((double) (clock() - t))/CLOCKS_PER_SEC; // in seconds
    // prints the seconds and the result of what it has returned
    printf("Time MiddleEven %f  returns: %s\n", time_taken, str);
 
    // second algorithm middleSlow (slowest)
    // sets current number of clocks as the new start clock count
    t = clock();
    // calls the algorithm middleSlow and assigns the returned value to str
    str = middleSlow(list)->name;
    // subtracts the number of clocks stored in 't' from the current number of clocks, giving us the true number of clocks. converts clocks to seconds and assigns it to time_taken
    time_taken = ((double) (clock() - t))/CLOCKS_PER_SEC; // in seconds
    // prints the seconds and the result of what it has returned
    printf("Time MiddleSlow %f  returns: %s\n", time_taken, str);
    
    // third algorithm (fastest)
    // sets current number of clocks as the new start clock count
    t = clock();
    // calls the algorithm middleZipZip and assigns the returned value to str
    str = middleZipZip(list)->name;
    // subtracts the number of clocks stored in 't' from the current number of clocks, giving us the true number of clocks. converts clocks to seconds and assigns it to time_taken
    time_taken = ((double) (clock() - t))/CLOCKS_PER_SEC; // in seconds
    // prints the seconds and the result of what it has returned
    printf("Time MiddleZipZip %f  returns: %s\n", time_taken, str);
    
    // fourth algorithm (true fastest, but predetermined)
    // sets current number of clocks as the new start clock count
    t = clock();
    // calls the algorithm middelCounter and assigns the returned value to str
    str = middleCounter(list, MYMIDDLE)->name;
    // subtracts the number of clocks stored in 't' from the current number of clocks, giving us the true number of clocks. converts clocks to seconds and assigns it to time_taken
    time_taken = ((double) (clock() - t))/CLOCKS_PER_SEC; // in seconds
    // prints the seconds and the result of what it has returned
    printf("Time MiddleCounter %f  returns: %s\n", time_taken, str);
}
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
node* prependNode(node* list, char* data){
    node *n = allocNode(list);
    n->next = list;
    list = n;
    list->name = data;
    return list;
}
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
void printList(node* list) {
    for(node* current = list;current != NULL;current = current->next) {
        printf("%s\n", current->name );
    }
    printf("\n");
    return;
}

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
