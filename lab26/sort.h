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

int *Min(node *head) {
    int *resultArr = malloc(sizeof(int) * 2);
    int min = __INT16_MAX__, index = 0, counter = 0;
    while (head != NULL) {
        if (min > head->value) {
            index = counter;
            min = head->value;
        }
        head = head->next;
        counter++;
    }
    resultArr[0] = min;
    resultArr[1] = index;
    return resultArr;
}

node *Sort(node *head) {
    if (head == NULL) {
        exit(-1);
    }
    int value, index, minValue, i = -1, c = 0;
    int *minR;
    node *tmp = NULL, *res = NULL;
    while (head) {
        value = head->value;
        Copy(&tmp, &head);
        minR = Min(tmp);
        head = NULL;
        index = minR[1];
        minValue = minR[0];
        while (tmp->next != NULL) {
            i++;
            if (i == index) {
                PushBack(value, &head);
                tmp = tmp->next;
                continue;
            }
            if (tmp->value == minValue) {
                if (c >= 0) {
                    PushBack(minValue, &res);
                }
                c++;
                tmp = tmp->next;
                continue;
            }
            PushBack(tmp->value, &head);
            tmp = tmp->next;
        }
        i = -1;
        PushBack(minValue, &res);
        DeleteList(&tmp);
        c = 0;
    }
    return res;
}