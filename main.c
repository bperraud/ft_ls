#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>


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

_options options;

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

int is_regular_file(const char *path) {
    struct stat st;
    if (stat(path, &st) == 0) {
        return S_ISREG(st.st_mode);
    } else {
        perror("stat");
        return 0;
    }
}

const char* print_basename(const char *path) {
    const char *base = strrchr(path, '/');
    if (base) {
        return base + 1;
    } else {
        return path;
    }
}

void print_regular_file(const char *path) {
    path = print_basename(path);
    if (is_regular_file(path)) {
        printf("%s\n", path);
    }
    else {
        printf("dir : %s\n", path);
    }
}

char *concat(const char *s1, const char *s2) {
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    char *result = malloc(len1 + len2 + 2);
    if (!result) return NULL;
    strcpy(result, s1);
    result[len1] = '/';
    result[len1 + 1] = '\0';
    strcat(result, s2);
    return result;
}


int ft_ls(char *path) {
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

    sort_ascii(entries, entries_number);


    if (options.is_reversed) {
        // Print in reverse
        for (ssize_t i = entries_number - 1; i >= 0; i--) {
            if (!options.include_hidden_files && entries[i]->d_name[0] == '.') {
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
                continue;
            }
            char *complete_path = concat(path, entries[i]->d_name);
            print_regular_file(complete_path);
            free(entries[i]);
            free(complete_path);
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
