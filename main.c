#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
    FORMAT_LONG,
    FORMAT_SINGLE_COLUMN,
    FORMAT_COLUMNS
} output_format_t;


typedef struct struct_options {
    output_format_t format;
    bool is_reversed;
    bool is_recursive;
    bool is_time_sorted;
    bool include_hidden_files;
} _options;


int ft_ls(char *path, _options options) {
    DIR *dir = opendir(path);

    if (!dir) {
        perror(path);
        return 1;
    }

    unsigned int entries_number = 0;
    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        entries_number += 1;
    }

    closedir(dir);

    struct dirent *entries[entries_number];
    dir = opendir(path);
    if (!dir) {
        perror(path);
        return 1;
    }

    int i = 0;
    while ((entry = readdir(dir)) != NULL) {
        entries[i] = malloc(sizeof(struct dirent));
        if (entries[i]) {
            memcpy(entries[i], entry, sizeof(struct dirent));
            i++;
        }
    }

    closedir(dir);

    // Print in reverse
    for (ssize_t i = entries_number - 1; i >= 0; i--) {
        printf("%s\n", entries[i]->d_name);
        free(entries[i]);
    }

    return 0;
}

int start(int argc, char **argv) {
    output_format_t format;

    _options options;

    if (isatty(STDOUT_FILENO)) {
        options.format = FORMAT_COLUMNS;
    } else {
        options.format = FORMAT_SINGLE_COLUMN;
    }

    // if (long_listing) {
    //     format = FORMAT_LONG;
    // }

    if (argc < 2) {
        ft_ls(".", options);
        return 0;
    }
    for (int i = 1; i < argc; i++) {
        ft_ls(argv[i], options);
    }
    return 0;
}

// int main(int argc, char **argv) {
//     return start(argc, argv);
// }
