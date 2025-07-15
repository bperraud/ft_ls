#include "header.h"
#include <stdio.h>




// typedef enum {
//     FORMAT_LONG,
//     FORMAT_SINGLE_COLUMN,
//     FORMAT_COLUMNS
// } output_format_t;

// typedef struct struct_print_len {
//     size_t uid;
//     size_t gid;
//     size_t size;
//     size_t datetime;
// } _print_max_len;

// typedef struct struct_options {
//     output_format_t format;
//     bool is_reversed;
//     bool is_recursive;
//     bool is_time_sorted;
//     bool include_hidden_files;
// } _options;


_options parse(int argc, char **argv) {
    _options options;

    // write(STDERR_FILENO, &argv[1][0], 1);

    options.include_hidden_files = false;
    options.is_reversed = false;
    options.is_recursive = false;
    options.is_time_sorted = false;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            int j = 0;
            while (argv[i][++j] != '\0') {
                if (argv[i][j] == 'l')
                    options.format = FORMAT_LONG;
                else if (argv[i][j] == 'R')
                    options.is_recursive = true;
                else if (argv[i][j] == 'a')
                    options.include_hidden_files = true;
                else if (argv[i][j] == 'r')
                    options.is_reversed = true;
                else if (argv[i][j] == 't')
                    options.is_time_sorted = true;
                else {
                    write(STDERR_FILENO, "ls: invalid option -- '", 22);
                    write(STDERR_FILENO, &argv[i][j], 1);
                    write(STDERR_FILENO, "'", 1);
                    perror(NULL);
                }
            }
            argv[i] = NULL;
        }
    }
    return options;
}
