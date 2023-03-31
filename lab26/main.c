#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
#define STACK_SIZE 30

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