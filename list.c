//add standard libraries which include function we need
#include <stdio.h>
#include <stdlib.h>


// Definition of a node structure
// a linked list is a data structure made up of node linked to each other
typedef struct node
{
    char* name;
    struct node* next;
}
node;

//main body of code where we will add to the list and print it out
int main(void)
{
    //initialization of list
    node *list = NULL;
    //initialization of first node
    node *n = malloc(sizeof(node));
    //checking if the memory that was allocated to the node is available
    if(n == NULL)
    {
        return 1;
    }
    //setting the node number to a number
    n->name = 1;
    //setting the next part of the list to blank/nothing
    n->next = NULL;
    //linking the list to the node
    list = n;
    
    //initializing the next node
    n = malloc(sizeof(node));
    if(n == NULL)
    {
        free(list);
        return 1;
    }
    n->name = 2;
    n->next = NULL;
    //linking the first node in the list to the second
    list->next = n;

    //initializing the next node
    n = malloc(sizeof(node));
    if(n == NULL)
    {
        free(list);
        free(n);
        return 1;
    }
    n->name = 3;
    n-> next = NULL;
    list->next->next = n;
    //printing out the nodes 1 by 1 using a loop
    //this loop intitializes a temporary node that stores each node of the list 
    //starts off at the first node which is the start of the list
    //continues untill the next node is NULL or blank
    for(node *tmp = list;tmp != NULL;tmp = tmp->next)
    {
        //prints current node
        printf("%i\n", tmp->name);
    }
}
