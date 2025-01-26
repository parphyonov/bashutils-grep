#include "s21_grep_parsers.h"

void parse_filenames(int fna_size, char **argv, char **filenames,
                     bool reg_or_files) {
  if (!reg_or_files)
    optind++;
  for (int i = 0; i < fna_size; i++, optind++) {
    strcpy(filenames[i], argv[optind]);
  }
}

void parse_options(int argc, char **argv, struct OptionsSet *options_set,
                   char **templates, char **ftemplates) {
  int fa_counter = 0;
  int ta_counter = 0;
  while (true) {
    int c;
    static struct option long_options[] = {
        {"regexp", required_argument, 0, 'e'},
        {"ignore-case", no_argument, 0, 'i'},
        {"invert-match", no_argument, 0, 'v'},
        {"count", no_argument, 0, 'c'},
        {"files-with-matches", no_argument, 0, 'l'},
        {"line-number", no_argument, 0, 'n'},
        {"no-filename", no_argument, 0, 'h'},
        {"no-messages", no_argument, 0, 's'},
        {"file", required_argument, 0, 'f'},
        {"only-matching", no_argument, 0, 'o'},
        {"check-and-print", no_argument, 0, 'd'},
        {0, 0, 0, 0}};

    int option_index = 0;

    c = getopt_long(argc, argv, "e:ivclnhsf:od", long_options, &option_index);

    // the end of the options was detected
    if (c == -1) {
      break;
    }

    switch (c) {
    case 'e':
      options_set->e_regexp = true;
      if (templates != NULL) {
        strcpy(templates[ta_counter], optarg);
        ta_counter++;
      }
      break;
    case 'i':
      options_set->i_ignore_case = true;
      break;
    case 'v':
      options_set->v_invert_match = true;
      break;
    case 'c':
      options_set->c_count = true;
      break;
    case 'l':
      options_set->l_files_with_matches = true;
      break;
    case 'n':
      options_set->n_line_number = true;
      break;
    case 'h':
      options_set->h_no_file_name = true;
      break;
    case 's':
      options_set->s_no_messages = true;
      break;
    case 'f':
      options_set->f_file = true;
      if (ftemplates != NULL) {
        strcpy(ftemplates[fa_counter], optarg);
        fa_counter++;
      }
      break;
    case 'o':
      options_set->o_only_matching = true;
      break;
    case 'd':
      options_set->check_and_print = true;
      break;
    case '?':
      printf("s21_grep: invalid option -- '%s'\n",
             long_options[option_index].name);
      print_usage();
      break;
    default:
      abort();
    }
  }
}