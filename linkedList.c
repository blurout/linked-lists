//standard libraries that include the functions we need
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//function prototypes; allow functions to be used without clutter of at the top of main
// Definition of a node structure
// a linked list is a data structure made up of node linked to each other
typedef struct node
{
    char* name;
    struct node* next;
}
node;
node* addNode(node *list, char* data);
node* allocNode(node *list);
node* insrtNodeBfr(node *list, char* data, char* nextData);
node* prepend(node *list, char* data);
node* insertNodeAftr(node *list, char* data, char* nextData);

int main(void)
{
    node* list = addNode(NULL,"Banana");
    addNode(list,"Cantaloupe");
    addNode(list,"Dragon Fruit");
    addNode(list,"Fig");
    insrtNodeBfr(list,"Elderberry", "Fig");
    insrtNodeBfr(list,"Blueberry", "Cantaloupe");
    insertNodeAftr(list, "Cherry", "Cantaloupe");
    list = prepend(list, "Apple");
    for(node *current = list;current != NULL;current = current->next){
        printf("%s\n", current->name );
    }


}
node* allocNode(node *list) {
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
node* addNode(node *list, char* data) {
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
node* insrtNodeBfr(node *list, char* data, char* nextData) {
    node *n = allocNode(list);
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
node* insertNodeAftr(node *list, char* data, char* beforeData) {
    node *n = allocNode(list);
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
node* prepend(node *list, char* data){
    node *n = allocNode(list);
    n->next = list;
    list = n;
    list->name = data;
    return list;
}
