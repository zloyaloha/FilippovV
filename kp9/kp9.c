#include <stdio.h>
#include <math.h> 
#include <stdbool.h>
#include <stdlib.h>
#define MAX_STRING_SIZE 100
#define MAX_TEXT_SIZE 100

typedef struct {
    char value[MAX_STRING_SIZE];
}line;

typedef struct {
    long s;
    long i;
    long j;
    long k;
}quat;

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
        return -1;
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

int Square(int num) {
    return num*num;
}

int SquaredNormOfQuat(quat q){
    return Square(q.s) + Square(q.i) + Square(q.j) + Square(q.k);
}

void SwapQ(quat *a, quat *b) {
    quat tmp = *a;
    *a = *b;
    *b = tmp;
}

void SwapL(line *a, line *b) {
    line tmp = *a;
    *a = *b;
    *b = tmp;
}

int Partition(quat *q, line *l, int left, int right) {
    quat medium = q[(left + right) >> 1];
    quat tmpQ;
    line tmpL;
    int i = left, j = right;
    while (i <= j) {
        while (SquaredNormOfQuat(q[i]) < SquaredNormOfQuat(medium)) {
            i++;
        }
        while (SquaredNormOfQuat(q[j]) > SquaredNormOfQuat(medium)) {
            j--;
        }
        if (i >= j) {
            break;
        }
        SwapL(&l[j], &l[i]);
        SwapQ(&q[i++], &q[j--]);
    }
    return j;
}

void QuickSort(quat *q, line *l, int n) {
    int left = 0, right = n - 1, medium = n >> 1, tmp[2];
    nodeS *s = NULL;
    PushL(&s, left, right);
    while (EmptyCheck(s)) {
        PopL(&s, tmp);
        if (tmp[1] <= tmp[0]) {
            continue;
        }
        int i = Partition(q, l, tmp[0], tmp[1]);
        if (i - tmp[0] < tmp[1] - i) {
            PushL(&s, tmp[0], i - 1);
            PushL(&s, i + 1, tmp[1]);
        } else {
            PushL(&s, i + 1, tmp[1]);
            PushL(&s, tmp[0], i - 1);
        }
    }
}

void PrintTable(line *l, quat *q, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d+%di+%dj+%dk\t%s\n", q[i].s, q[i].i, q[i].j, q[i].k, l[i].value);
    }
}

int BinarySearch(quat *q, int n, quat aim) {
    int left = 0, right = n, m;
    while (left <= right) {
        int sqnAIM = SquaredNormOfQuat(aim);
        int sqnM = SquaredNormOfQuat(q[m]);
        m = (right + left) / 2;
        if (SquaredNormOfQuat(aim) == SquaredNormOfQuat(q[m])) {
            left = m;
            break;
        }
        if (SquaredNormOfQuat(aim) < SquaredNormOfQuat(q[m])) {
            right = m + 1;
        } else {
            left = m - 1;
        }
    }
    if (SquaredNormOfQuat(q[left]) == SquaredNormOfQuat(aim)) {
        return left;
    } else {
        printf("Key not found\n");
    }
    return -1;
}

int main(int argc, char *argv[]) {
    FILE *f;
    line l[MAX_TEXT_SIZE];
    quat q[MAX_TEXT_SIZE];
    quat test;
    test.s = 1;
    test.i = 2;
    test.j = 3;
    test.k = 4;

    int n = 0;
    // if (argc != 2) {
    //     printf("Use: program_name input_file\n");
    //     return 0;
    // }
    if ((f = fopen("/home/linux-zloyaloha/MAI/programming/labs-first-course/kp9/data.csv", "r")) == NULL) {
        printf("Can not open file\n");
        return 0;
    }
    while (!feof(f)) {
        fscanf(f, "%d+%di+%dj+%dk;%[^'\n']", &q[n].s, &q[n].i, &q[n].j, &q[n].k, &l[n]);
        n++;
    }
    // int bin = BinarySearch(q, n, test);
    PrintTable(l,q,n);
    putchar('\n');
    QuickSort(q, l, n);
    PrintTable(l,q,n);
    // printf("%d+%di+%dj+%dk \t %s", q[bin].s, q[bin].i, q[bin].j, q[bin].k, l[bin].value);
}