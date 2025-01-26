#ifndef __S21_GREP_PARSERS
#define __S21_GREP_PARSERS

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_grep_helpers.h"
#include "s21_grep_options_set.h"

// парсит названия файлов из командной строки и заполняет ими массив
void parse_filenames(int fna_size, char **argv, char **filenames,
                     bool reg_or_files);

// парсит опции и заполняет два массива
void parse_options(int argc, char **argv, struct OptionsSet *options_set,
                   char **templates, char **ftemplates);

#endif