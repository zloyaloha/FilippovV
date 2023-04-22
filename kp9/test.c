#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Stack{
    int left;
    int right;
    struct Stack *next;
}nodeS;

void PushL(nodeS **head, int l, int r){
    nodeS *tmp = (nodeS *)malloc(sizeof(nodeS));
    tmp->left = l;
    tmp->right = r;
    tmp->next = (*head);
    (*head) = tmp;
}

int* PopL(nodeS **head, int *value) {
    if (*head == NULL) {
        perror("List is empty");
        exit(-1);
    }
    nodeS *tmp = (*head);
    value[0] = tmp->left;
    value[1] = tmp->right;
    (*head) = (*head)->next;
    free(tmp);
    return value;
}

bool EmptyCheck(nodeS *head) {
    return head != NULL ? true : false;
}

void Swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int Partition(int *q, int left, int right) {
    int medium = q[(left + right) / 2];
    int i = left, j = right;
    while (i < j) {
        while (q[i] < medium) {
            i++;
        }
        while (q[j] > medium) {
            j--;
        }
        if (i >= j) {
            break;
        }
        Swap(&q[i++], &q[j--]);
    }
    return j;
}

void QuickSort(int *q, int n) {
    int left = 0, right = n - 1, medium = n >> 1, tmp[2];
    nodeS *s = NULL;
    PushL(&s, left, right);
    while (EmptyCheck(s)) {
        PopL(&s, tmp);
        if (tmp[1] <= tmp[0]) {
            continue;
        }
        int border = Partition(q, tmp[0], tmp[1]);
        if (border - tmp[0] > tmp[1] - border) {
            PushL(&s, tmp[0], border - 1);
            PushL(&s, border + 1, tmp[1]);
        } else {
            PushL(&s, border + 1, tmp[1]);
            PushL(&s, tmp[0], border - 1);
        }
    }
    for (int i = 0; i < 7; i++) {
        printf("%d ", q[i]);
    }
}

int main() {
    int a[7] = {3, 8, 9, 3, 4, 1, 2};
    QuickSort(a, 7);
}