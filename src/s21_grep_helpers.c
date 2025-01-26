#include "s21_grep_helpers.h"

void print_usage(void) {
  printf("Usage: s21_grep [options] template [file_name]\n");
}

int count_lines(const char *filename) {
  FILE *file = fopen(filename, "r");
  int lines = 0;

  if (file != NULL) {
    char ch;
    while ((ch = fgetc(file)) != EOF) {
      if (ch == '\n')
        lines++;
    }
    fclose(file);
  } else
    lines = -1;

  lines = lines + 1;
  return lines;
}

int count_tmp_size(int argc, char **argv) {
  int counter = 0;
  for (int i = 1; i < argc; i++)
    if (argv[i][0] == '-' && argv[i][1] != '-' && (strstr(argv[i], "e")))
      counter++;
  if (counter == 0)
    counter = 1;
  return counter;
}

int count_ftmp_size(int argc, char **argv) {
  int counter = 0;
  for (int i = 1; i < argc; i++)
    if (argv[i][0] == '-' && strstr(argv[i], "f"))
      counter++;
  return counter;
}

void fill_extra_templates(char **extra_templates, int eta_size,
                          char **ftemplates, int fta_size) {
  int eta_counter = 0;
  while (eta_counter < eta_size) {
    for (int i = 0; i < fta_size; i++) {
      FILE *file = fopen(ftemplates[i], "r");
      if (file != NULL) {
        char line[LINE_MAX];
        while (fgets(line, sizeof(line), file)) {
          if (line[strlen(line) - 1] == '\n') {
            strncpy(extra_templates[eta_counter], line, strlen(line) - 1);
            extra_templates[eta_counter][strlen(line) - 1] = '\0';
          } else
            strcpy(extra_templates[eta_counter], line);
          eta_counter++;
        }
      } else {
        printf("s21_grep: failed to read from Template File -- %s\n",
               ftemplates[i]);
        exit(4);
      }
      fclose(file);
    }
  }
}

char **init_strings_array(int size, const size_t MAX_SIZE, char *label) {
  char **array = (char **)malloc(size * sizeof(char *));
  if (array != NULL) {
    for (int i = 0; i < size; i++) {
      array[i] = (char *)malloc(MAX_SIZE * sizeof(char));
      if (array[i] == NULL) {
        printf("s21_grep: failed to initiate %s [%d]\n", label, i);
        exit(5);
      }
    }
  } else {
    printf("s21_grep: failed to initiate %s\n", label);
    exit(6);
  }
  return array;
}

void free_strings_array(char **array, int size) {
  if (array != NULL) {
    for (int i = 0; i < size; i++)
      free(array[i]);
    free(array);
  }
}

void check_and_print_string_array_for_content(char **array, int size,
                                              char *label) {
  if (array != NULL) {
    printf("%s [ size=%d ]\n", label, size);
    for (int i = 0; i < size; i++)
      printf("\t>>> %s\n", array[i]);
  }
}

void run_checkblock(char **array1, int size1, char *label1, char **array2,
                    int size2, char *label2, char **array3, int size3,
                    char *label3, char **array4, int size4, char *label4) {
  printf("\n\n--- CHECKBLOCK ---\n");

  printf("\033[0;33m");
  printf("/ to suppress this message don't use '-d' or '--check-and-print'/");
  printf("\033[0m\n");

  check_and_print_string_array_for_content(array1, size1, label1);
  check_and_print_string_array_for_content(array2, size2, label2);
  check_and_print_string_array_for_content(array3, size3, label3);
  check_and_print_string_array_for_content(array4, size4, label4);
}