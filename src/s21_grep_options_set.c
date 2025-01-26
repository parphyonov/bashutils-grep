#include "s21_grep_options_set.h"

void init_all_oset_to_false(struct OptionsSet *options_set) {
  options_set->e_regexp = false;
  options_set->i_ignore_case = false;
  options_set->v_invert_match = false;
  options_set->c_count = false;
  options_set->l_files_with_matches = false;
  options_set->n_line_number = false;
  options_set->h_no_file_name = false;
  options_set->s_no_messages = false;
  options_set->f_file = false;
  options_set->o_only_matching = false;
  options_set->check_and_print = false;
}
