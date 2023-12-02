#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  char c;
  int total = 0;
  char f = 'a';
  char l = 'a';
  char string[2];
  FILE *inputs = fopen("test.txt", "r");
  if (inputs == NULL) {
    printf("cannot open file");
  }

  while (c != EOF) {
    c = fgetc(inputs);
    int digit = isdigit(c);
    if (digit && !isdigit(f)) {
      f = c;
      l = c;
    } else if (digit && isdigit(f)) {
      l = c;
    }
    if (c == '\n') {
      if (!isdigit(l)) {
        l = f;
      }
      string[0] = f;
      string[1] = l;
      int number = atoi(string);
      total += number;
      f = 'a';
      l = 'a';

    }
  }
  printf("%d\n", total);
  fclose(inputs);
  return 0;
}
