#include <stdio.h>
#include <string.h>
#include <error.h>
#include <stdlib.h>
#define CAPACITY 4
#define NUM 1
#define SPACE 2
#define ENTER 3
#define END 4

typedef struct Coordinates {
    int column;
    int string;
    int value;
}coord;

typedef struct MaxNIndex {
    int value;
    int index;
} max;

typedef struct ListC {
    struct ListC *next;
    coord data;
} nodeC;

typedef struct ListM {
    struct ListM *next;
    max data;
} nodeM;

void PushBackM(nodeM **head, max data) {
    nodeM *tmp = (nodeM*) malloc(sizeof(nodeM));
    tmp->data = data;
    tmp->next = (*head);
    (*head) = tmp;
}

nodeM* GetLastM(nodeM *head) {
    if (head == NULL) {
        return NULL;
    }
    while (head->next) {
        head = head->next;
    }
    return head;
}

void PushM(nodeM *head, max value) {
    nodeM *last = GetLastM(head);
    nodeM *tmp = (nodeM*)malloc(sizeof(nodeM));
    tmp->data = value;
    tmp->next = NULL;
    last->next = tmp;
}

max PopM(nodeM **head) {
    max val;
    nodeM *tmp = NULL;
    if (*head == NULL) {
        exit(-1);
    }
    tmp = *head;
    val = tmp->data;
    (*head) = (*head)->next;
    free(tmp);
    return val;
}

int ClayNum(char c, int num, int flag) {
    if (flag == 1) {
        num *= 10;
    }
    num += c - '0';
    return num;
}

void PushBackC(nodeC **head, coord data) {
    nodeC *tmp = (nodeC*) malloc(sizeof(nodeC));
    tmp->data = data;
    tmp->next = (*head);
    (*head) = tmp;
}

nodeC* GetLastC(nodeC *head) {
    if (head == NULL) {
        return NULL;
    }
    while (head->next) {
        head = head->next;
    }
    return head;
}

void PushC(nodeC *head, coord value) {
    nodeC *last = GetLastC(head);
    nodeC *tmp = (nodeC*)malloc(sizeof(nodeC));
    tmp->data = value;
    tmp->next = NULL;
    last->next = tmp;
}

coord PopC(nodeC **head) {
    coord val;
    nodeC *tmp = NULL;
    if (*head == NULL) {
        exit(-1);
    }
    tmp = *head;
    val = tmp->data;
    (*head) = (*head)->next;
    free(tmp);
    return val;
}


int StateUpdate(char c) {
    if (c == '\n') {
        return ENTER;
    } else if (c == ' ') {
        return SPACE;
    } else if (c >= '0' && c <= '9') {
        return NUM;
    } else {
        return END;
    }
}

void CoordinateMatrixOutput(nodeC *arr) {
    while(arr) {
        printf("[%d %d %d]\n", (arr->data).column, (arr->data).string, (arr->data).value);
        arr = arr->next;
    }
}

void MatrixInput(FILE *in, nodeC **listC, int *str, int *col) {
    coord cord;
    char c;
    int state = 0, number = 0, flag = 0, inI = 0, inJ = 0;
    while (1) {
        if (flag == 2) {
            break;
        }
        c = fgetc(in);
        state = StateUpdate(c);
        switch (state){
        case NUM:
            number = ClayNum(c, number, flag);
            flag = 1;
            break;
        case SPACE: 
            if (number != 0) {
                cord.column = inJ;
                cord.string = inI;
                cord.value = number;
                PushC(*listC, cord);
            }
            number = 0;
            inI += 1;
            flag = 0;
            break;
        case ENTER:
            if (number != 0) {
                cord.column = inJ;
                cord.string = inI;
                cord.value = number;
                PushC(*listC, cord);
            }
            number = 0;
            inI = 0;
            inJ += 1;
            flag = 0;
            break;
        default:
            if (number != 0) {
                cord.column = inJ;
                cord.string = inI;
                cord.value = number;
                PushC(*listC, cord);
            }
            flag = 2;
            break;
        }
    }
    *str = inJ + 1;
    *col = inI + 1;
    printf("____________________________\n");
}


char InArr(nodeC *arr, int j, int k) {
    arr = arr->next;
    while (arr) {
        if ((arr->data).column == j && (arr->data).string == k) {
            return (arr->data).value;
        }
        arr = arr->next;
    }
    return 0;
}

void UsualMatrixOutput(nodeC *arr, int str, int col) {
    int n = 0;
    for (int j = 0; j < str; j++) {
        for (int k = 0; k < col; k++) {
            if (n = InArr(arr, j, k)) {
                printf("%d ", n);
            } else {
                printf("0 ");
            }
        }
        putchar('\n');
    }
}

nodeM *MaxElementOfMatrix(nodeC *head) {
    max maximum;
    nodeM *res = NULL;
    maximum.index = -1;
    maximum.value = -1;
    while (head) {
        if ((head->data).value >= maximum.value) {
            maximum.value = (head->data).value;
            maximum.index = (head->data).column;
            PushBackM(&res, maximum);
        }
        head = head->next;
    }
    return res;
}

nodeC *Del(nodeC *listC, int index, int data) {
    nodeC *head = listC;
    while (listC) {
        if ((listC->data).column == index) {
            (listC->data).value = (listC->data).value / data;
        }
        listC = listC->next;
    }
    listC = head;
    return listC;
}

void Task(nodeC **listC) {
    nodeM *maxEls = NULL;
    int index, data;
    maxEls = MaxElementOfMatrix(*listC);
    while ((maxEls->data).value == (maxEls->next->data).value) {
        index = (maxEls->data).index;
        data = (maxEls->data).value;
        *listC = Del(*listC, index, data);
        maxEls = maxEls->next;
    }
    index = (maxEls->data).index;
    data = (maxEls->data).value;
    *listC = Del(*listC, index, data);
}

int main(int argc, char *argv[]) {
    // if (argc != 2) {
    //     printf("input err");
    //     return 2;
    // }
    int col = 0, str = 0;
    coord z;
    z.column = -1;
    z.string = -1;
    z.value = -1;
    nodeC *listC = NULL;
    PushBackC(&listC, z);
    FILE * in = fopen("input", "r");
    MatrixInput(in, &listC, &str, &col);
    CoordinateMatrixOutput(listC);
    printf("________________________\n");
    UsualMatrixOutput(listC, str, col);
    Task(&listC);
    printf("________________________\n");
    UsualMatrixOutput(listC, str, col);
    // while (maxEls) {
    //     printf("%d %d\n", (maxEls->data).index, (maxEls->data).value);
    //     maxEls = maxEls->next;
    // }
}