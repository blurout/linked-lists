#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct node {
    char* name;
    struct node* next;
}
node;

void printList(node* list);
node* appendNode(node *list, char* data);
node* allocNode(node *list);
node* insertNodeBefore(node *list, char* data, char* nextData);
node* prependNode(node *list, char* data);
node* insertNodeAfter(node *list, char* data, char* nextData);
node* reverseList(node *list);
node* removeNode(node* list, char* data);

node* middleEven(node* list);
node* middleSlow(node* list);
node* middleZipZip(node* list);
node* middleCounter(node* list, int MYMIDDLE);

int main(void) {
    node* list = appendNode(NULL,"Banana");
    appendNode(list,"Cantaloupe");
    appendNode(list,"Dragon Fruit");
    appendNode(list,"Fig");

    // insertNodeBefore(list,"Elderberry", "Fig");
    // insertNodeBefore(list,"Blueberry", "Cantaloupe");
    // insertNodeAfter(list, "Cherry", "Cantaloupe");
    // list = prependNode(list, "Apple");
    // printList(list);
    // list = reverseList(list);
    // printList(list);
    // list = removeNode(list, "Fig");
    //printList(list);

    clock_t t;
    const int NUMNODES = 1500000;
    const int MYMIDDLE = NUMNODES/2;
    for(int i = 0; i <= NUMNODES; i++) {
        char* istr = malloc(sizeof(char*));
        appendNode(list, itoa (i,istr,10));
    }
    double time_taken = 0;

    t = clock();
    char* str = middleEven(list)->name;
    time_taken = ((double) (clock() - t))/CLOCKS_PER_SEC; // in seconds
    printf("Time MiddleEven %f  returns: %s\n", time_taken, str);
    
    t = clock();
    str = middleSlow(list)->name;
    time_taken = ((double) (clock() - t))/CLOCKS_PER_SEC; // in seconds
    printf("Time MiddleSlow %f  returns: %s\n", time_taken, str);
    
    t = clock();
    str = middleZipZip(list)->name;
    time_taken = ((double) (clock() - t))/CLOCKS_PER_SEC; // in seconds
    printf("Time MiddleZipZip %f  returns: %s\n", time_taken, str);
    
    t = clock();
    str = middleCounter(list, MYMIDDLE)->name;
    time_taken = ((double) (clock() - t))/CLOCKS_PER_SEC; // in seconds
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
