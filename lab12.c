#include <stdio.h>

#define SIGN 0
#define NUM 1
#define CONTINUE 2

int Abs(int n) {
    return n = (n > 0) ? n : -n;
}

void DoubOutput(char doub[]) {
    for (int i = 0; i < 8; i++) {
        putchar(doub[i]);
    }
}

void ToDouble(char num, char sign) {
    int i = 1;
    char doub[8] = "00000000";
    while (Abs(num) > 0) {
        doub[8-i] = (Abs(num) % 2) + '0';
        num /= 2;
        ++i;
    }
    if (sign == '-') {
       for (int i = 0; i < 8; ++i) {
            doub[i] = (doub[i] == '0') ? '1' : '0';
        }
        for (int i = 7; i > 0; --i) {
            if (doub[i] == '0') {
                doub[i] = '1';
                break;
            } else {
                doub[i] = '0';
            }
        }
        doub[0] = '1';
    } 
     DoubOutput(doub);   
    putchar('\n');
}

int StatusUpdate(char ch, char *sign){
    if (ch >= '0' && ch <= '9') {
        return NUM;
    } else if (ch == '-') {
        *sign = '-';
        return SIGN;
    } else {
        return CONTINUE;
    }
}

char ClayNum(char ch, int k, char num, char sign){
    if (sign == '+') {
       if (k == 0) {
        num += ch - '0';
    } else if (k == 1) {
        num *= 10;
        num += ch - '0';
    } else if (k == 2) {
        num *= 10;
        num += ch - '0';
    }
    } else {
    if (k == 0) {
        num -= ch - '0';
    } else if (k == 1) {
        num *= 10;
        num -= ch - '0';
    } else if (k == 2) {
        num *= 10;
        num -= ch - '0';
    }
    }
    return num;
}

int main() {
    char ch, sign = '+', num = ' ' - 32;
    int state = CONTINUE;
    int k = 0;
    while ((ch = getchar()) != EOF){

        state = StatusUpdate(ch, &sign);

        if (state == NUM) {
            num = ClayNum(ch, k, num, sign);
            ++k;
        } else if (state == CONTINUE) {
            ToDouble(num, sign);
        num = ' ' - 32;
        k = 0;
        sign = '+';
        }
    }
}
