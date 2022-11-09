//* Филиппов Владимир М80-110Б-22 *//
//* Кодирование по Цезарю с переменным ключом +3 *//
//* Тесты: don li Volga li te4et kotomku na ple40 *//
//* qwertyuiopasdfghjklzxcvbnm *// 
//* Viva Victoria *//

#include <stdio.h>

#define ENTER 0
#define IN_DIGIT 1
#define CONTINUE 2
#define SPACE 3

int AsciiCode(char c, int counter) {
    int ascii = 0;
    if ((int)c >= 65 && (int)c <= 90){
        ascii = (counter + 3 + (int)(c) - 65) % 26 + 65;
    } else {
        ascii = (counter + 3 + (int)(c) - 97) % 26 + 97;
    }
    return ascii;
}
int SpaceCheck(char c){
    if (c == ' '){
        return 0;
    }
    return 1;
}

int EnterCheck(char c){
    if (c == '\n'){
        return 1;
    }
    return 0;
}

int GarbageCheck(char c){
    int intc = (int)c;
    if ((intc >= 1 && intc <= 64 || intc >= 91 && intc <= 96 || intc >= 123) && c != '\n'){
        return 1;
    }
    return 0;
}

int main(){
    char c;
    int counter = 0, ascii = 0;
    int state = 0;
    while ((c = getchar()) != EOF){
        if (SpaceCheck(c)){
            ++counter;
            if (GarbageCheck(c)){
                state = CONTINUE;
            } else {
                state = IN_DIGIT;
                if (EnterCheck(c)){
                    state = ENTER;
                    counter = 0;    
                }
            }
        } else {
            state = SPACE;
            counter = 0;
        }
    
        if (state == IN_DIGIT){
            putchar(AsciiCode(c, counter));
        } else if (state == CONTINUE){
            putchar(c);
        } else if (state == SPACE){
            putchar(' ');
        } else if (state == ENTER){
            putchar('\n');
        }
    }
    
    return 0;
}   