#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct node {
    int data;
    struct node* next;
}
node;

node* allocNode(node* head);
node* appendNode(node* head, int data);
int bi2dec(node* head);
int dec2bi(node* head);

int main(void) {


    node* list = appendNode(NULL, 1);
    appendNode(list, 0);
    appendNode(list, 1);
    printf("%i\n", bi2dec(list));
    printf("%i", dec2bi(list));

}

node* allocNode(node* head) {
    node* n = malloc(sizeof(node));
    if(n == NULL){
        node *tmp = head->next;
        while(head != NULL) {
            tmp = head->next;
            free(head);
            head = tmp;
        }
    }
    return n;
}
node* appendNode(node* head, int data) {
    node* n = allocNode(head);
    if(n != NULL) {
        n->data = data;
        n->next = NULL;
        if(head == NULL) {
            return n;
        }
        while(head->next != NULL) {
            head = head->next;
        }
        head->next = n;
    }
    return n;
}
int bi2dec(node* head) {
    int len = 0;
    node* list = head;
    while(head->next != NULL) {
        head = head->next;
        len++;
    }
    if(len <= 1 && head->data == 0) {
        return 0;
    }
    int decimal = 0;
    while (list != NULL) {
        if(list->data != 0) {
            decimal += pow(2, len);
        }
        len--;
        list = list->next;
    }
    return decimal;
}
int dec2bi(node* head) {
    int len = 0;
    node* list = head;
    while(head->next != NULL) {
        head = head->next;
        len++;
    }
    if(len <= 1 && head->data == 0) {
        return 0;
    }
    int binary = 0;
    while (list != NULL) {
        if(list->data != 0) {
            binary += pow(10, len);
        }
        len--;
        list = list->next;
    }
    return binary;
}