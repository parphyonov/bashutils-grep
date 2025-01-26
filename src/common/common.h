#ifndef __S21_CAT_GREP_COMMON
#define __S21_CAT_GREP_COMMON

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void create_files(char* fn1, char* fn2);
void delete_files(char* fn1, char* fn2);

int compare_files(char* fn1, char* fn2, bool debug);

#endif