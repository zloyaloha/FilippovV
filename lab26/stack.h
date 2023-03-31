#include <stdio.h>
#include <stdlib.h>

typedef struct nodeS {
    int value;
    struct nodeS* next;
} node;

void DeleteList(node **head) {
    node* prev = NULL;
    while ((*head)->next) {
        prev = (*head);
        (*head) = (*head)->next;
        free(prev);
    }
    free(*head);
    *head = NULL;
}

void Print(node *head){
    if (head) {
        printf("%d<-", head->value);
        Print(head->next);
    } else {
        printf("NULL\n");
    }
}

void PushBack(int value, node **head) {
    node *newNode = (node *)malloc(sizeof(node));
    newNode->value = value;
    newNode->next = *head;
    *head = newNode;
}

int Pop(node **head) {
    node *tmp = NULL;
    int val;
    if (head == NULL) {
        exit(-1);
    }
    tmp = *head;
    val = (*head)->value;
    (*head) = (*head)->next;
    free(tmp);
    return val;
}

void Copy(node **target, node **orig) {
    node* prev = NULL;
    while ((*orig)->next) {
        PushBack((*orig)->value, target);
        prev = (*orig);
        (*orig) = (*orig)->next;
        free(prev);
    }
    PushBack((*orig)->value, target);
    free(*orig);
}
