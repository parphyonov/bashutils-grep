CC=gcc
C_FLAG=-c
STD_FLAGS=-Wall -Werror -Wextra -std=c11
VG_FLAGS=--tool=memcheck --leak-check=yes --track-origins=yes

all: main

main: clean s21_grep

s21_grep: s21_grep.o s21_grep_helpers.o s21_grep_options_set.o s21_grep_parsers.o s21_grep_printer.o
	$(CC) $(STD_FLAGS) s21_grep.o s21_grep_helpers.o s21_grep_options_set.o s21_grep_parsers.o s21_grep_printer.o -o s21_grep

s21_grep.o: s21_grep.c s21_grep_helpers.h s21_grep_options_set.h s21_grep_parsers.h
	$(CC) $(C_FLAG) $(STD_FLAGS) s21_grep.c -o s21_grep.o

s21_grep_helpers.o: s21_grep_helpers.c s21_grep_helpers.h
	$(CC) $(C_FLAG) $(STD_FLAGS) s21_grep_helpers.c -o s21_grep_helpers.o

s21_grep_options_set.o: s21_grep_options_set.c s21_grep_options_set.h
	$(CC) $(C_FLAG) $(STD_FLAGS) s21_grep_options_set.c -o s21_grep_options_set.o

s21_grep_parsers.o: s21_grep_parsers.c s21_grep_parsers.h s21_grep_helpers.h
	$(CC) $(C_FLAG) $(STD_FLAGS) s21_grep_parsers.c -o s21_grep_parsers.o

s21_grep_printer.o: s21_grep_printer.c s21_grep_printer.h s21_grep_options_set.h s21_grep_helpers.h
	$(CC) $(C_FLAG) $(STD_FLAGS) s21_grep_printer.c -o s21_grep_printer.o

clean:
	rm -rf *.o

fc:
	clang-format -i *.c
	clang-format -i *.h

cpp:
	cppcheck --enable=all --suppress=missingIncludeSystem ./*.c

