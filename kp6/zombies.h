#ifndef DEADMEN_H
#define DEADMEN_H

typedef struct {
    char surname[25];
    char initials[2];
    int age;
    char sex;
    char birtday[11];
    char deadday[11];
    int relatives;
    char tombstone;
} zombie;
#endif