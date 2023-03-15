#ifndef STACK_H
#define STACK_H
#include <stdio.h>
#include <stdlib.h>

typedef struct nodeS {
    int value;
    struct nodeS *prev;
    struct nodeS *next;
} node;

void DeleteList(node **head);
void Print(node *head);
void PushBack(int value, node **head);
int Pop(node **head);
void Copy(node **target, node **orig);

#endif 