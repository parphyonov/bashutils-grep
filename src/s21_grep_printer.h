#ifndef __S21_GREP_PRINTER
#define __S21_GREP_PRINTER

#include <ctype.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_grep_helpers.h"
#include "s21_grep_options_set.h"

// превращает все символы строки в их аналоги в нижнем регистре
void str_to_lowercase(char *line);

// ищет регулярное выражение, с учетом регистра
bool regsearch(char *fft, char *template, char *line, bool i_ignore_case);

// главная функция, производит поиск и печать согласно заданным настройкам
void start_grep_printer(struct OptionsSet options_set, char **templates,
                        int ta_size, char **extra_templates, int eta_size,
                        char **filenames, int fna_size, int fni,
                        bool *matches_present);

// совершает стандартные операции со строкой
void line_subroutine(struct OptionsSet options_set, FILE *file, char *line,
                     char **filenames, int fna_size, int fni, size_t line_num,
                     bool *last_line, char *fft, size_t *matching_lines);

#endif