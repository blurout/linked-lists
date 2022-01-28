#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node {
    char* name;
    struct node* next;
}
node;
//fixed var and func names
node* appendNode(node *list, char* data);
node* allocNode(node *list);
node* insertNodeBefore(node *list, char* data, char* nextData);
node* prependNode(node *list, char* data);
node* insertNodeAfter(node *list, char* data, char* nextData);
node* reverseList(node *list);

int main(void) {
    node* list = appendNode(NULL,"Banana");
    appendNode(list,"Cantaloupe");
    appendNode(list,"Dragon Fruit");
    appendNode(list,"Fig");
    insertNodeBefore(list,"Elderberry", "Fig");
    insertNodeBefore(list,"Blueberry", "Cantaloupe");
    insertNodeAfter(list, "Cherry", "Cantaloupe");
    list = prependNode(list, "Apple");
    list = reverseList(list);
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

