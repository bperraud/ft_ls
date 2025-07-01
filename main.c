#include "header.h"
#include <string.h>
#include <sys/types.h>

_options options;

const char* path_basename(const char *path) {
    const char *base = strrchr(path, '/');
    if (base) {
        return base + 1;
    } else {
        return path;
    }
}

void print_regular_file(const char *path) {
    const char *file_name = path_basename(path);
    printf("%s\n", file_name);
}

void sort_ascii(struct dirent *entries[], size_t count) {
    for (size_t i = 0; i < count - 1; i++) {
        for (size_t j = 0; j < count - i - 1; j++) {
            if (strcmp(entries[j]->d_name, entries[j + 1]->d_name) > 0) {
                // Swap pointers
                struct dirent *tmp = entries[j];
                entries[j] = entries[j + 1];
                entries[j + 1] = tmp;
            }
        }
    }
}

int ft_ls(const char *path) {

    if (options.is_recursive && !strcmp(path, ".")) {
        printf(".:\n");
    }

    if (is_regular_file(path)) {
        print_regular_file(path);
        return 0;
    }

    DIR *dir = opendir(path);

    if (!dir) {
        perror(path);
        return 1;
    }

    unsigned int entries_number = 0;
    unsigned int dir_number = 0;
    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        entries_number += 1;
        char *total_path = concat(path, entry->d_name);
        if (!is_regular_file(total_path)) {
            // printf("path : %s\n", total_path);
            dir_number += 1;
        }
        free(total_path);
    }

    closedir(dir);

    struct dirent *entries[entries_number];
    char *dir_entries[dir_number];
    dir = opendir(path);
    if (!dir) {
        perror(path);
        return 1;
    }

    int i = 0;
    int dir_index = 0;
    while ((entry = readdir(dir)) != NULL) {
        entries[i] = malloc(sizeof(struct dirent));
        if (entries[i]) {
            memcpy(entries[i], entry, sizeof(struct dirent));
            char *comp_path = concat(path, entries[i]->d_name);
            if (!is_regular_file(comp_path) && strcmp(comp_path + strlen(comp_path) - 2, "/.") && strcmp(comp_path + strlen(comp_path) - 3, "/..") && strcmp(comp_path, "./.git")) {
                dir_entries[dir_index] = strdup(comp_path);
                dir_index += 1;
            }
            free(comp_path);
            i++;
        }
    }

    closedir(dir);
    sort_ascii(entries, entries_number);

    if (options.is_reversed) {
        // Print in reverse
        for (ssize_t i = entries_number - 1; i >= 0; i--) {
            if (!options.include_hidden_files && entries[i]->d_name[0] == '.') {
                free(entries[i]);
                continue;
            }
            char *complete_path = concat(path, entries[i]->d_name);
            print_regular_file(complete_path);
            free(entries[i]);
            free(complete_path);
        }
    }
    else {
        for (ssize_t i = 0; i < entries_number; i++) {
            if (!options.include_hidden_files && entries[i]->d_name[0] == '.') {
                free(entries[i]);
                continue;
            }
            char *complete_path = concat(path, entries[i]->d_name);
            print_regular_file(complete_path);
            free(entries[i]);
            free(complete_path);
        }
    }

    if (options.is_recursive) {
        for (ssize_t i = 0; i < dir_index; i++) {
            printf("\n");
            printf("%s:\n", dir_entries[i]);
            ft_ls(dir_entries[i]);
            free(dir_entries[i]);
        }
    }

    return 0;
}


int start(int argc, char **argv) {
    output_format_t format;

    if (isatty(STDOUT_FILENO)) {
        options.format = FORMAT_COLUMNS;
    } else {
        options.format = FORMAT_SINGLE_COLUMN;
    }

    options.include_hidden_files = false;
    options.is_reversed = false;
    options.is_recursive = true;

    // if (long_listing) {
    //     format = FORMAT_LONG;
    // }

    if (argc < 2) {
        ft_ls(".");
        return 0;
    }
    for (int i = 1; i < argc; i++) {
        ft_ls(argv[i]);
    }
    return 0;
}

// int main(int argc, char **argv) {
//     return start(argc, argv);
// }
