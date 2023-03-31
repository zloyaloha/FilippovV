
#define CAPACITY 2
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct tree
{
    char *key;
    struct tree *left;
    struct tree *right;
    struct tree *parent;
} tnode;

typedef struct StackNodesP {
    struct StackNodesP *next;
    tnode *data;
} nodeP;

typedef struct StackNodesC {
    struct StackNodesC *next;
    char data;
} nodeC;

// реализация вектора чаров 
void PushBackL(char *arr, char value, int *capacity, int *size){
    if (*size >= *capacity){
        arr = realloc(arr, sizeof(arr) * 2);
        *capacity *= 2;
    }
    arr[*size] = value; 
    *size += 1;
}


void PrintL(char *arr, int size){
    for (int i = 0; i < size; i++) {
        printf("%c", arr[i]);
    }
    putchar('\n');
}
// --------------

// реализация стека для чаров
void PushC(nodeC **head, char value){
    nodeC *tmp = (nodeC *)malloc(sizeof(nodeC));
    tmp->data = value;
    tmp->next = *head;
    *head = tmp;
}

int PopC(nodeC **head) {
    char val;
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
// ------------------

void PushN(nodeP **head, tnode *value){
    tnode *copyValue = value;
    nodeP *tmp = (nodeP *)malloc(sizeof(nodeP));
    tmp->data = copyValue;
    tmp->next = *head;
    *head = tmp;
}

tnode *PopN(nodeP **head) {
    tnode *val;
    nodeP *tmp = NULL;
    if (*head == NULL) {
        exit(-1);
    }
    tmp = *head;
    val = tmp->data;
    (*head) = (*head)->next;
    free(tmp);
    return val;
}

char IsDigit(char c) {
    if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')) {
        return 1;
    }
    return 0;
}

char IsOperator(char c) {
    switch ((int)c)
    {
    case 41:
        return -1;
    case 40:
        return 1;
    case 43:
        return 2;
    case 45:
        return 2;
    case 42:
        return 3;
    case 47:
        return 3;
    case 94:
        return 4;
    default:
        return 0;
    }
}

char *PostFix(char *arr, int *size) {
    int capacity = CAPACITY, sizeR = 0, priority, c = 0;
    char *res = malloc(sizeof(char) * CAPACITY);
    nodeC *head = NULL;
    if (size == 0) {
        printf("Input is empty");
        return "";
    }
    PushC(&head, 0);
    for (int i = 0; i < *size; i++) {
        if (IsDigit(arr[i])) {
            PushBackL(res, arr[i], &capacity, &sizeR);
            c++;
        } else if (priority = IsOperator(arr[i])) {
            if (c > 0){
                PushBackL(res, ' ', &capacity, &sizeR);
                c = 0;
            }
            if (priority > 1) { // случай с обычным оператом (не скобкой)
                while (IsOperator(head->data) >= priority) {
                    PushBackL(res, PopC(&head), &capacity, &sizeR);
                    PushBackL(res, ' ', &capacity, &sizeR);
                }
                PushC(&head, arr[i]);
            } else if (priority == 1) { // случай если скобка (
                PushC(&head, arr[i]);
            } else if (priority == -1) { // случай если скобка )
                while (head->data != '(') {
                    PushBackL(res, PopC(&head), &capacity, &sizeR);
                    PushBackL(res, ' ', &capacity, &sizeR);
                }

                PopC(&head);
            }
        }
    }
    while(head->next) {
        if (res[sizeR-1] != ' ') {
            PushBackL(res, ' ', &capacity, &sizeR);
        }
        PushBackL(res, PopC(&head), &capacity, &sizeR);
    }
    *size = sizeR;
    return res;
}

tnode *MakeTree(char *data, tnode *left, tnode *right) {
    tnode *tmp = (tnode *)malloc(sizeof(tnode));
    char *copyData = (char *)malloc(sizeof(data));
    memccpy(copyData, data, ' ', 5);
    tmp->key = copyData;
    tmp->left = left;
    tmp->right = right;
    return tmp;
}

tnode *MathTree(char *arr, int size) {
    int j, k = 0;
    char symb[5], copySymb[5];
    if (size == 0) {
        return NULL;
    }
    nodeP *stack = NULL;
    for (int i = 0; i < size; i++) {
        j = i;
        for (int j = 0; j < 5; j++) {
            symb[j] = '!';
        }
        while (arr[j] != ' ' && j <= size) {
            symb[k] = arr[j];
            k++;
            j++;
        }
        i = j;
        k = 0;
        if (IsOperator(symb[0])) {
            tnode * x = PopN(&stack);
            tnode * y = PopN(&stack);
            tnode *node = MakeTree(symb, x, y);
            PushN(&stack, node);
        } else {
            tnode *symbN = MakeTree(symb, NULL, NULL);
            PushN(&stack, symbN);
        }

    }
    return PopN(&stack);
}

void Task(tnode **root) {
    if (*root == NULL) {
        return;
    }
    tnode *tmp = NULL; 
    if (*((*root)->key) == '*' && *((*root)->left->key) == '/' && *((*root)->right->key) == '/') {
        *((*root)->left->key) = '*';
        *((*root)->right->key) = '*';
        *((*root)->key) = '/';
        tmp = (*root)->right->left;
        (*root)->right->left = (*root)->left->right;
        (*root)->left->right = tmp;
    }
    Task(&((*root)->left));
    Task(&((*root)->right));
}

void InOrder(tnode *root) {
    int i = 0;
    if (root == NULL) {
        return;
    }
    if (IsOperator(*(root->key))) {
        printf("(");
    }
    InOrder(root->right);
    while (root->key[i] != '!') {
        printf("%c", root->key[i]);
        i++;
    }
    InOrder(root->left);
    if (IsOperator(*(root->key))) {
        printf(")");
    }
}

int main(){
    int capacity = CAPACITY, size = 0;
    char ch;
    char *arr = malloc(sizeof(char) * CAPACITY);
    tnode *mathTree = NULL;
    putchar('\n');
    printf("Print expression without spaces: ");
    while (ch != EOF) {
        ch = getchar();
        if (ch == ' ' || ch == '\n' || ch == ',') {
            arr = PostFix(arr, &size);
            mathTree = MathTree(arr, size);

            printf("______________________________________\n");
            putchar('\n');
            printf("Expression in original view: ");
            InOrder(mathTree);
            putchar('\n');

            printf("Expression in polish notation: ");
            PrintL(arr, size);

            printf("Expression in after some mathematical transformations: ");
            Task(&mathTree);
            InOrder(mathTree);
            putchar('\n');
            printf("______________________________________\n");

            free(arr);
            free(mathTree);
            char *arr = malloc(sizeof(char) * CAPACITY);
            tnode *mathTree = NULL;
            putchar('\n');
            printf("Print expression without spaces: ");
        } else {
            PushBackL(arr, ch, &capacity, &size);
        }
    }
    
}