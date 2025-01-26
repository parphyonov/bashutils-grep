#ifndef __S21_GREP_OPTIONS_SET
#define __S21_GREP_OPTIONS_SET

#include <stdbool.h>

// структура для работы с опциями
struct OptionsSet {
  bool e_regexp;
  bool i_ignore_case;
  bool v_invert_match;
  bool c_count;
  bool l_files_with_matches;
  bool n_line_number;
  bool h_no_file_name;
  bool s_no_messages;
  bool f_file;
  bool o_only_matching;
  bool check_and_print;
};

// настраивает все параметры структуры на значение ЛОЖЬ
void init_all_oset_to_false(struct OptionsSet *options_set);

#endif