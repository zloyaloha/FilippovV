#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "sort.h"

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

