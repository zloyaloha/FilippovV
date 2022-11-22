#include <stdio.h>

#define NUM 1
#define SPACE 2
#define ENTER 3
#define END 4
#define MAXN 8
#define GROUP 110


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

int ClayNum(char c, int num, int flag) {
    if (flag == 1) {
        num *= 10;
    }
    num += c - '0';
    return num;
}

int main() {
    int n = 1, state = 0, flag = 0, number = 0, inI = 0, inJ = 0;
    int a[MAXN][MAXN];
    int b[MAXN][MAXN];
    char c;
    while (1) {
        c = getchar();
        state = StateUpdate(c);
        if (state == NUM) {
            number = ClayNum(c, number, flag);
            flag = 1;
        } else if (state == SPACE) {
            a[inJ][inI] = number;
            b[inJ][inI] = number;
            number = 0;
            inI += 1;
            flag = 0;
        } else if (state == ENTER) {
            a[inJ][inI] = number;
            b[inJ][inI] = number;
            number = 0;
            if (inJ == 0) {
                n = inI + 1;
            }
            inI = 0;
            inJ += 1;
            flag = 0;
        } else {
            a[inI][inJ] = number;
            b[inJ][inI] = number;
            inJ += 1;
            break;
        }
    }
    
    
    for (int k = 0;  k < GROUP; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != n - 1) {
                    a[i + 1][j] = b[i][j];
                } else {
                    a[0][j] = b[n-1][j];
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                b[i][j] = a[i][j];
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", a[i][j]);
        }
        putchar('\n');
    }
    putchar('\n');
}
