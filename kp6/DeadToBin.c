#include <stdio.h>
#include <string.h>
#include <error.h>
#include "zombies.h"

int ReadDeadmen(FILE *in, zombie *z){
    return fscanf(in, "%[^' '] %[^\t]\t%d\t%c\t%[^\t] %[^\t]\t%d\t%c\n", z->surname, z->initials, &z->age, &z->sex, &z->birtday, &z->deadday, &z->relatives, &z->tombstone) == 8;
}

int main(int argc, char* argv[]) {
    char c;
    if (argc != 3) {
        printf("Usage: program input_filename output_filename\n");
        return 1;
    }
    // data.csv
    // out.bin
    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "wb");
    zombie z;
    if (!(in && out)) {
        perror("READING/CREATING ERROR");
        return 2;
    }
    
    while (ReadDeadmen(in, &z)) {
        fwrite(&z, sizeof (z), 1, out);
    }
    return 0;
}