#include <stdio.h>
#include <string.h>
#include <error.h>
#include <stdlib.h>
#include "zombies.h"
#define CAPACITY 32


void PushBackL(zombie *arr, zombie value, int *capacity, int *size){
    if (*size >= *capacity){
        arr = realloc(arr, sizeof(arr) * 2);
        *capacity *= 2;
    }
    arr[*size] = value; 
    *size += 1;
}

int NumberOfRelatives(FILE *in) {
    int p;
    int capacity = CAPACITY, size = 0, priority, c = 0;
    zombie z;
    zombie *arr = (zombie *)malloc(sizeof(zombie) * CAPACITY);
    printf("Print number of relatives: ");
    scanf("%d", &p);
    while (fread(&z, sizeof(z), 1, in) == 1) {
        if (z.relatives > p) {
            PushBackL(arr, z, &capacity, &size);
        }
    }
    if (size > 0) {
        printf("_____________________________________________________________________________________________________________\n");
        printf("|        SURNAME          | IN | AGE | SEX |    BIRTDAY    |    DEADDAY    | NUMBER OF RELATIVES | TOMBSTONE |\n");
        printf("_____________________________________________________________________________________________________________\n");
        for (int i = 0; i < size; i++) {
            printf("|%-25s|%-4s|%-5d|%-5c|%-15s|%-15s|%-21d|%-11c|\n", arr[i].surname, arr[i].initials, arr[i].age, arr[i].sex, arr[i].birtday, 
            arr[i].deadday, arr[i].relatives, arr[i].tombstone);
        }
        printf("_____________________________________________________________________________________________________________\n");
    }
    printf("Database has %d deadmen with more than %d number of relatives\n", size, p);
}

int TableOutput(FILE *in) {
    if (!in) {
        perror("Can not open file\n");
        return 3;
    }
    printf("_____________________________________________________________________________________________________________\n");
    printf("|        SURNAME          | IN | AGE | SEX |    BIRTDAY    |    DEADDAY    | NUMBER OF RELATIVES | TOMBSTONE |\n");
    printf("_____________________________________________________________________________________________________________\n");
    zombie z;
    while (fread(&z, sizeof(z), 1, in) == 1) {
        printf("|%-25s|%-4s|%-5d|%-5c|%-15s|%-15s|%-21d|%-11c|\n", z.surname, z.initials, z.age, z.sex, z.birtday, 
            z.deadday, z.relatives, z.tombstone);
    }
            printf("_____________________________________________________________________________________________________________\n");
    }

int main(int argc, char *argv[]) {
    if (argc != 3){
        printf("Usage: program -key inputfile\n");
        return 1;
    }
    FILE *in = fopen(argv[2], "rb");
    if (strcmp(argv[1], "-f") == 0) {
        TableOutput(in);
    } else if (strcmp(argv[1], "-p") == 0) {
        NumberOfRelatives(in);
    } else {
        printf("KEY ERROR\n");
        return 2;
    }

}