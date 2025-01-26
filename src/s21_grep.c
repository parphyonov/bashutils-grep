#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "s21_grep_helpers.h"
#include "s21_grep_options_set.h"
#include "s21_grep_parsers.h"
#include "s21_grep_printer.h"

// s21_grep [options] template [file_names]
int main(int argc, char **argv) {
  if (argc < 3) {
    printf("s21_cat: absolutely no arguments were provided\n");
    exit(1);
  }

  int ftmp_size = count_ftmp_size(argc, argv);
  // >>> файлы с регулярными выражениями из -f <<<
  char **template_files = NULL;
  char ft_label[32] = "TEMPLATE FILES\0";
  if (ftmp_size > 0)
    template_files = init_strings_array(ftmp_size, STR_MAX, ft_label);

  int tmp_size = count_tmp_size(argc, argv);
  // >>> регулярные выражения от пользователя из -e или без <<<
  char **templates = NULL;
  char t_label[32] = "TEMPLATES\0";
  if (tmp_size > 0)
    templates = init_strings_array(tmp_size, STR_MAX, t_label);

  // >>> структура для работы с опциями <<<
  struct OptionsSet oset;
  init_all_oset_to_false(&oset);
  parse_options(argc, argv, &oset, templates, template_files);

  if (!(oset.e_regexp) && argc - optind != 1)
    strcpy(templates[0], argv[optind]);

  int etmp_size = 0;
  // >>> дополнительные регулярки из файлов -f <<<
  char **extra_templates = NULL;
  char et_label[32] = "EXTRA TEMPLATES\0";

  if (ftmp_size > 0) {
    for (int i = 0; i < ftmp_size; i++) {
      if (count_lines(template_files[i]) != -1)
        etmp_size += count_lines(template_files[i]);
      else {
        printf("s21_grep: failed to read a template file -- %s\n",
               template_files[i]);
        exit(2);
      }
    }
    if (etmp_size > 0) {
      extra_templates = init_strings_array(etmp_size, LINE_MAX, et_label);
      fill_extra_templates(extra_templates, etmp_size, template_files,
                           ftmp_size);
    }
  }

  if (oset.f_file && tmp_size == 1 && etmp_size > 0)
    strcpy(templates[0], extra_templates[0]);

  // >>> имена файлов для поиска <<<
  char **filenames = NULL;
  char fn_label[32] = "FILENAMES\0";
  int offset = 1;

  if (oset.e_regexp || oset.f_file)
    offset = 0;

  int fn_size = argc - optind - offset;
  if (fn_size > 0)
    filenames = init_strings_array(fn_size, STR_MAX, fn_label);
  else
    printf("s21_grep: utility can't work without a single file to read from\n");

  parse_filenames(fn_size, argv, filenames, oset.e_regexp || oset.f_file);

  bool matches_present = false;
  for (int i = 0; i < fn_size; i++)
    start_grep_printer(oset, templates, tmp_size, extra_templates, etmp_size,
                       filenames, fn_size, i, &matches_present);
  if (!matches_present)
    exit(3);

  // используй флаг -d или --check-and-print для вывода содержимого массивов
  if (oset.check_and_print)
    run_checkblock(template_files, ftmp_size, ft_label, templates, tmp_size,
                   t_label, extra_templates, etmp_size, et_label, filenames,
                   fn_size, fn_label);

  // >>> освобождаем память <<<
  free_strings_array(extra_templates, etmp_size);
  free_strings_array(template_files, ftmp_size);
  free_strings_array(templates, tmp_size);
  free_strings_array(filenames, fn_size);

  return 0;
}