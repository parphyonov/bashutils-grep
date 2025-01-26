#ifndef __S21_GREP_HELPERS
#define __S21_GREP_HELPERS

#define STR_MAX 256
#define LINE_MAX 1024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// печатает сообщение о стандартном использовании программы
void print_usage(void);

// считает количество строк в файле
int count_lines(const char *filename);
// считает размер для инициализации массива регулярных выражений
int count_tmp_size(int argc, char **argv);
// считает размер для инициальизации массива названий файлов с рег. выр.
int count_ftmp_size(int argc, char **argv);

// заполняет содержимым массив с рег. выр.
void fill_extra_templates(char **extra_templates, int eta_size,
                          char **ftemplates, int fta_size);

// инициализирует стандартный массив строк
char **init_strings_array(int size, const size_t MAX_SIZE, char *label);
// освобождает память в стандартном массиве строк
void free_strings_array(char **array, int size);

// печаетает содержимое массива строк
void check_and_print_string_array_for_content(char **array, int size,
                                              char *label);
// печатает содержимое всех четырех использованных массивов
void run_checkblock(char **array1, int size1, char *label1, char **array2,
                    int size2, char *label2, char **array3, int size3,
                    char *label3, char **array4, int size4, char *label4);

#endif