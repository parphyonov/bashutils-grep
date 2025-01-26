#include "s21_grep_printer.h"

bool is_last_line(FILE *file) {
  bool result = false;
  if (feof(file))
    result = true;
  else {
    int next_char = fgetc(file);
    if (next_char == EOF)
      result = true;
    else
      ungetc(next_char, file);
  }
  return result;
}

void str_to_lowercase(char *line) {
  for (size_t c = 0; c < strlen(line); c++)
    line[c] = tolower(line[c]);
}

bool regsearch(char *fft, char *template, char *line, bool i_ignore_case) {
  bool is_found = false;
  regex_t regex;
  regmatch_t matches[1];
  int result = regcomp(&regex, template, 0);
  if (result != 0) {
    printf("s21_grep: failed to compile a regex\n");
    exit(7);
  }
  if (i_ignore_case) {
    str_to_lowercase(line);
    str_to_lowercase(template);
  }
  int match_result = regexec(&regex, line, 1, matches, 0);
  if (match_result == 0) {
    is_found = true;
    int start = matches[0].rm_so;
    int end = matches[0].rm_eo;
    strncpy(fft, line + start, end - start);
  } else if (match_result == REG_NOMATCH)
    is_found = false;
  regfree(&regex);
  return is_found;
}

void start_grep_printer(struct OptionsSet options_set, char **templates,
                        int ta_size, char **extra_templates, int eta_size,
                        char **filenames, int fna_size, int fni,
                        bool *matches_present) {
  FILE *file = fopen(filenames[fni], "r");

  if (file != NULL) {
    char line[LINE_MAX];
    char tmpline[LINE_MAX];
    size_t line_num = 0;
    size_t matching_lines = 0;

    while (fgets(line, sizeof(line), file)) {
      strcpy(tmpline, line);
      bool found = false;
      bool last_line;
      char fft[STR_MAX] = "\0";
      while (true) {
        for (int ti = 0; ti < ta_size; ti++)
          found = found || regsearch(fft, templates[ti], tmpline,
                                     options_set.i_ignore_case);
        for (int eti = 0; eti < eta_size; eti++)
          found = found || regsearch(fft, extra_templates[eti], tmpline,
                                     options_set.i_ignore_case);
        break;
      }
      *matches_present = *matches_present || found;
      line_num++;
      if (!options_set.v_invert_match && found) {
        line_subroutine(options_set, file, line, filenames, fna_size, fni,
                        line_num, &last_line, fft, &matching_lines);
      } else if (options_set.v_invert_match && !found) {
        line_subroutine(options_set, file, line, filenames, fna_size, fni,
                        line_num, &last_line, fft, &matching_lines);
      }
    }
    if (options_set.c_count && fna_size > 1)
      printf("%s:", filenames[fni]);
    if (options_set.c_count)
      printf("%zu\n", matching_lines);
    if (options_set.l_files_with_matches && matching_lines > 0)
      printf("%s\n", filenames[fni]);
    fclose(file);
  } else {
    if (!options_set.s_no_messages)
      printf("s21_grep: %s: No such file or directory\n", filenames[fni]);
  }
}

void line_subroutine(struct OptionsSet options_set, FILE *file, char *line,
                     char **filenames, int fna_size, int fni, size_t line_num,
                     bool *last_line, char *fft, size_t *matching_lines) {
  if (!options_set.c_count && !options_set.l_files_with_matches) {
    if (fna_size > 1)
      if (!options_set.h_no_file_name)
        printf("%s:", filenames[fni]);
    if (options_set.n_line_number)
      printf("%zu:", line_num);
    if (!options_set.o_only_matching) {
      printf("%s", line);
      *last_line = is_last_line(file);
      if (*last_line)
        printf("\n");
    } else
      printf("%s\n", fft);
  }
  *matching_lines = *matching_lines + 1;
}