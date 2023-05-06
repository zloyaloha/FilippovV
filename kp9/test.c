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
    for (int k = 0; k < 9; k++) {
        printf("%d ", q[k]);
    }
    putchar('\n');
    do {
        while (q[i] < medium) {
            i++;
        }
        while (q[j] > medium) {
            j--;
        }
        if (i <= j) {
            Swap(&q[i], &q[j]);
            i++;
            j--;
        } else {
            break;
        }
    } while (i <= j);

    for (int k = 0; k < 9; k++) {
        printf("%d ", q[k]);
    }
    putchar('\n');
    printf("%d\n", medium);
    return i;
}

void QuickSort(int *q, int n) {
    int left = 0, right = n - 1, tmp[2];
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
            PushL(&s, border, tmp[1]);
            printf("1(%d %d) (%d %d)\n", tmp[0], border - 1, border, tmp[1]);
        } else {
            PushL(&s, border, tmp[1]);
            PushL(&s, tmp[0], border - 1);
            printf("2(%d %d) (%d %d)\n", border, tmp[1], tmp[0], border - 1);
        }
    }
    // for (int i = 0; i < 13; i++) {
    //     printf("%d ", q[i]);
    // }
}

int main() {
    int a[9] = { 156, 133, 201, 169, 82, 119, 135, 165, 50};
    QuickSort(a, 9);
    for (int i = 0; i < 9; i++) {
        printf("%d ", a[i]);
    }
}