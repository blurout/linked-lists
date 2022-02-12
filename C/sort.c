#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

typedef struct node{
    int val;
    node* next;
} 
node;

void printList(node* list);
node* allocNode(node *list);
node* prependNode(node *list, int data);

node* bubbleSort(node* list);
node* mergeSort(node* list);
node* quickSort(node* list);
node* insertionSort(node* list);


int main(void) {
}

