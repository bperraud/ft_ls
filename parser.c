#include "header.h"
#include <stdio.h>

_options parse(int argc, char **argv) {
    _options options;

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
