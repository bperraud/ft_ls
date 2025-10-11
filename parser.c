#include "header.h"

_options parse(int argc, char **argv) {
    _options options = {};

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            int j = 0;
            while (argv[i][++j] != '\0') {
                if (argv[i][j] == 'l')
                    options.is_long_format = true;
                else if (argv[i][j] == 'R')
                    options.is_recursive = true;
                else if (argv[i][j] == 'a')
                    options.include_hidden_files = true;
                else if (argv[i][j] == 'r')
                    options.is_reversed = true;
                else if (argv[i][j] == 't')
                    options.is_time_sorted = true;
                else {
                    write(STDERR_FILENO, "ft_ls: invalid option -- '", 23);
                    write(STDERR_FILENO, &argv[i][j], 1);
                    write(STDERR_FILENO, "'\n", 2);
                    exit(1);
                }
            }
            argv[i] = NULL;
        }
    }
    return options;
}
