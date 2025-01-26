#include "common.h"

void create_files(char* fn1, char* fn2) {
  char command[64];
  sprintf(command, "touch %s %s", fn1, fn2);
  system(command);
}

void delete_files(char* fn1, char* fn2) {
  char command[64];
  sprintf(command, "rm -rf %s %s", fn1, fn2);
  system(command);
}

int compare_files(char* fn1, char* fn2, bool debug) {
  int result = 0;

  FILE* file1 = fopen(fn1, "r");
  FILE* file2 = fopen(fn2, "r");

  if (file1 != NULL && file2 != NULL) {
    char ch1, ch2;
    while ((ch1 = fgetc(file1)) != EOF && (ch2 = fgetc(file2)) != EOF) {
      if (debug) {
        printf(">>> >>> [%c][%i] +++ [%c][%i]\n", ch1, ch1, ch2, ch2);
      }
      if (ch1 != ch2) {
        result = 1;
        break;
      }
    }
    fclose(file1);
    fclose(file2);
  } else {
    result = 2;
  }
  return result;
}

// int main(int argc, char** argv) {
//   int result = 0;
//   if (argc > 1) {
//     printf("%s", argv[0]);
//     create_files("f1", "f2");
//     result = compare_files("f1", "f2", false);
//     delete_files("f1", "f2");
//   }
//   return result;
// }
