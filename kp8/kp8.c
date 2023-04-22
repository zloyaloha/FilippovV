#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#define ARRAY_SIZE 50


typedef enum Color {
    black,
    white,
    red,
    yellow,
    green,
    blue,
    orange,
    gray,
    brown
} color;

typedef struct ListOfColors {
    struct ListOfColors *next;
    color data;
} nodeC;

void PrintL(nodeC *head){
    if (head == NULL) {
        printf("|\n");

        return;
    }
    printf("%d->", head->data);
    PrintL(head->next);
}

void PushL(color value, nodeC **head){
    nodeC *tmp = (nodeC *)malloc(sizeof(nodeC));
    tmp->data = value;
    tmp->next = (*head);
    (*head) = tmp;
}

nodeC *GetLastL(nodeC *head) {
    if (head == NULL){
        return NULL;
    }
    while (head->next) {
        head = head->next;
    }
    return head;
}

int Length(nodeC *head){
    int c = 0;
    while (head) {
        c++;
        head = head->next;
    }
    return c;
}

void PushBackL(color value, nodeC **head) {
    nodeC *tmp = (nodeC *)malloc(sizeof(nodeC));
    nodeC *last = GetLastL(*head);
    if (last == NULL) {
        PushL(value, head);
    } else {
        tmp->data = value;
        tmp->next = NULL;
        last->next = tmp;
    }
}

color PopL(nodeC **head) {
    color value;
    if (*head == NULL) {
        perror("List is empty");
        return -1;
    }
    nodeC *tmp = (*head);
    value = tmp->data;
    (*head) = (*head)->next;
    free(tmp);
    return value;
}

nodeC *GetNthElement(nodeC *head, int n){
    int i = 0;
    while (i < n) {
        if (head == NULL) {
            perror("N element doesn't exists");
            return NULL;
        }
        i++;
        head = head->next;
    }
    return head;
}

void InsertAfterN(nodeC *head, color value, int n) {
    nodeC *elemN = GetNthElement(head, n);
    if (elemN == NULL) {
        return;
    }
    nodeC *tmp = (nodeC *)malloc(sizeof(nodeC));
    tmp->data = value;
    tmp->next = elemN->next;
    elemN->next = tmp;
}

color PopNthElement(nodeC **head, int n) {
    if (n > Length(*head)) {
        perror("N element doesn't exists");
        return -1;
    }
    if (n == 0) {
        return PopL(head);
    } else {
        color value;
        nodeC *prev = GetNthElement(*head, n-1);
        nodeC *elemN = prev->next;
        value = elemN->data;
        prev->next = elemN->next;
        free(elemN);
        return(value);
    }
}

color *ListToArray(color *array, nodeC *head) {
    int i = 0;
    if (head == NULL) {
        perror("List is empty");
        exit(-1);
    }
    while (head->next != NULL && i < ARRAY_SIZE) {
        array[i] = head->data;
        head = head->next;
        i++;
    }
    return array;
}

void DeleteLastKElements(nodeC **head, int k) {
    int length = Length(*head);
    int c = 1;
    if (length < k) {
        perror("K is bigger then length");
        return;
    } else {
        while (k > 0) {
            PopNthElement(head, length - c);
            c++;
            k--;
        }
    }
}

void ConsoleLines(int n){
    for (int i = 0; i < n; i++) {
        printf("~");
    }
    putchar('\n');
}

int main() {
    nodeC *list = NULL;
    int choose;
    bool f1 = true;
    while (f1) {
        ConsoleLines(89);
        printf("| 1. Print list | 2. Insert in list | 3. Delete from list | 4. Size | 5. Task | 6. Exit |\n");
        ConsoleLines(89);
        printf("Print your choice: ");
        scanf("%d", &choose);
        switch (choose) {
            case 1: {
                putchar('\n');
                PrintL(list);
                putchar('\n');
                break;
            }
            case 2: {
                int chooseAdd;
                bool f2 = true;
                color car;
                while (f2) {
                    ConsoleLines(117);
                    printf("| 1. Adding into the start | 2. Adding to the end | 3. Adding to Nth position | 4. Random filling of list | 5. Exit |\n");
                    ConsoleLines(117);
                    printf("Print your choice: ");
                    scanf("%d", &chooseAdd);
                    switch(chooseAdd) {
                        case 1: {
                            printf("Print color: ");
                            scanf("%d", &car);
                            PushL(car, &list);
                            break;
                        }
                        case 2: {
                            printf("Print color: ");
                            scanf("%d", &car);
                            PushBackL(car, &list);
                            break;
                        }
                        case 3: {
                            int pos;
                            printf("Print color: ");
                            scanf("%d", &car);
                            printf("Print position: ");
                            scanf("%d", &pos);
                            InsertAfterN(list, car, pos);
                            break;
                        }
                        case 4: {
                            int quantity;
                            printf("Print quantity of list: ");
                            scanf("%d", &quantity);
                            for (int i = 0; i < quantity; i++) {
                                PushBackL(rand() % 9, &list);
                            }
                            putchar('\n');
                            break;
                        }
                        case 5: {
                            f2 = false;
                            break;
                        }
                    }
                }
                break;
            }
            case 3: {
                int chooseDel;
                bool f3 = true;
                while (f3) {
                    ConsoleLines(67);
                    printf("| 1. Deleting from the start | 2. Deleting Nth position | 3. Exit |\n");
                    ConsoleLines(67);
                    printf("Print your choice: ");
                    scanf("%d", &chooseDel);
                    putchar('\n');
                    switch (chooseDel) {
                        case 1: {
                            PopL(&list);
                            break;
                        }
                        case 2: {
                            int pos;
                            printf("Print position for deleting: ");
                            scanf("%d", &pos);
                            PopNthElement(&list, pos);
                            break;
                        } 
                        case 3: {
                            f3 = false;
                            break;
                        }
                    }
                }
                break;
            }
            case 4: {
                printf("Length of list: %d\n", Length(list));
                break;
            }
            case 5: {
                int chooseTask;
                bool f4 = true;
                while (f4) {
                    ConsoleLines(50);
                    printf("| 1. Delete last k elements | 2. Exit |\n");
                    ConsoleLines(50);
                    printf("Print your choice: ");
                    scanf("%d", &chooseTask);
                    putchar('\n');
                    switch (chooseTask) {
                        case 1: {
                            int k;
                            printf("Type k amount of deleting elements: ");
                            scanf("%d", &k);
                            DeleteLastKElements(&list, k);
                            break;
                        }
                        case 2: {
                            f4 = false;
                            break;
                        }
                    }
                }
                break;
            }
            case 6: {
                f1 = false;
                break;
            }
        }
    }
}