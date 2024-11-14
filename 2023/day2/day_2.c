#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

int convert(char* p, int l);

int main(void) {
    char* buffer;
    long file_size;
    FILE* file = fopen("test.txt", "rb");

    int total = 0;

    int id = 0;
    int id_count = 2;
    char p[3] = { 0, 0, 0 };
    char holder;

    int red = 0;
    int blue = 0;
    int green = 0;
    char v[2] = { 0, 0 };
    int v_count = 1;

    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    buffer = (char*)malloc(file_size + 1);
    
    fread(buffer, 1, file_size, file);

    fclose(file);
    buffer[file_size] = '\0';

    for (int i = 0; i < file_size; i++) {
        if (buffer[i] == ':') {
            int j = i - 1;
            holder = buffer[j]; 
            while(isdigit(holder)) {
                p[id_count] = holder;
                id_count--;
                j--;
                holder = buffer[j];
            }
            id = convert(p, 3);
            id_count = 2;
        }
        if ((buffer[i] == 'r' && buffer[i - 1] != 'g') || buffer[i] == 'g' || buffer[i] == 'b') {
            int j = i - 2;
            holder = buffer[j];
            while(isdigit(holder)) {
                v[v_count] = holder;
                v_count--;
                j--;
                holder = buffer[j];
            }
            buffer[i] == 'r' ? red = convert(v, 2) : buffer[i] == 'g' ? green = convert(v, 2) : buffer[i] == 'b' ? blue = convert(v, 2) : 0;
            v_count = 1;
        } 
        if (red > 12 || green > 13 || blue > 14) {
            printf("%d\n", red);
            id = 0;
        }
        if (buffer[i] == ';') {
            red = 0;
            blue = 0;
            green = 0;
        }
        if (buffer[i] == '\n') {
            printf("id: %d is valid\n", id);
            total += id;
            red = 0;
            blue = 0;
            green = 0;
        }
    } 
    printf("%d\n", total);
    free(buffer);
}


int convert(char* p, int l) {
    int result = 0;
    for (int i = 0; i < l; i++) {
        if (p[i] - '0' >= 0) {
            result = result * 10 + (p[i] - '0');
        }
        p[i] = 0;
    }
    return result;
}
