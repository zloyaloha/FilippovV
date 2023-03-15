#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#define STACK_SIZE 69

int main() {
    node *head = NULL;
    node *tmp = NULL;
    for (int i = 0; i < STACK_SIZE; i++) {
        PushBack(rand() % 100, &head);
    }
    Print(head);
    head = Sort(head);
    Print(head);
}