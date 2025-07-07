#include "header.h"
#include <stddef.h>
#include <string.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>
#include <time.h>

_options options;

const char* path_basename(const char *path) {
    const char *base;

    base = strrchr(path, '/');
    if (base) {
        return base + 1;
    } else {
        return path;
    }
}

void print_permissions(mode_t mode) {
    char perms[11] = {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'};

    // file type
    if (S_ISDIR(mode)) perms[0] = 'd';
    else if (S_ISLNK(mode)) perms[0] = 'l';
    else if (S_ISCHR(mode)) perms[0] = 'c';
    else if (S_ISBLK(mode)) perms[0] = 'b';
    else if (S_ISSOCK(mode)) perms[0] = 's';
    else if (S_ISFIFO(mode)) perms[0] = 'p';
    // user
    if (mode & S_IRUSR) perms[1] = 'r';
    if (mode & S_IWUSR) perms[2] = 'w';
    if (mode & S_IXUSR) perms[3] = 'x';
    // group
    if (mode & S_IRGRP) perms[4] = 'r';
    if (mode & S_IWGRP) perms[5] = 'w';
    if (mode & S_IXGRP) perms[6] = 'x';
    // others
    if (mode & S_IROTH) perms[7] = 'r';
    if (mode & S_IWOTH) perms[8] = 'w';
    if (mode & S_IXOTH) perms[9] = 'x';

    printf("%s ", perms);
}


char * get_ctime_ls_format(time_t mod_time) {
    char *full;

    full = ctime(&mod_time);
    full[16] = '\0';
    return full + 4;
}

void string_format(size_t len, size_t max_len) {
    for (int i = len; i < max_len; i++) {
        putchar(' ');
    }
}

void print_regular_file(const char *path, _print_max_len *print_max_len) {
    struct stat st;
    const char *file_name;
    char *st_size_str;

    if (options.format == FORMAT_LONG) {
        if (lstat(path, &st) != 0) {
            perror("lstat");
            exit(1);
        }
        print_permissions(st.st_mode);
        printf("%s ", getpwuid(st.st_uid)->pw_name);
        string_format(strlen(getpwuid(st.st_uid)->pw_name), print_max_len->uid);
        printf("%s ", getgrgid(st.st_gid)->gr_name);
        string_format(strlen(getgrgid(st.st_gid)->gr_name), print_max_len->gid);
        st_size_str = ft_itoa(st.st_size);
        string_format(strlen(st_size_str), print_max_len->size);
        free(st_size_str);
        printf("%ld ", st.st_size);
        printf("%s ", get_ctime_ls_format(st.st_mtime));
        if (S_ISLNK(st.st_mode)) {
            printf("It's a symbolic link\n");
        }
    }
    file_name = path_basename(path);
    printf("%s\n", file_name);
}


void get_max_line_length(const char *path, _print_max_len *print_max_len) {
    unsigned int    len = 0;
    struct stat     st;
    const char *    file_name;
    char *          st_size_str;

    if (lstat(path, &st) != 0) {
        perror("lstat");
        exit(1);
    }
    print_max_len->uid = MAX(strlen(getpwuid(st.st_uid)->pw_name), print_max_len->uid);
    print_max_len->gid = MAX(strlen(getgrgid(st.st_gid)->gr_name), print_max_len->gid);
    st_size_str = ft_itoa(st.st_size);
    print_max_len->size = MAX(strlen(st_size_str), print_max_len->size);
    print_max_len->datetime = MAX(strlen(get_ctime_ls_format(st.st_mtime)), print_max_len->datetime);
    free(st_size_str);
}

void sort_ascii(struct dirent *entries[], size_t count) {
    struct dirent *tmp;

    for (size_t i = 0; i < count - 1; i++) {
        for (size_t j = 0; j < count - i - 1; j++) {
            if (strcmp(entries[j]->d_name, entries[j + 1]->d_name) > 0) {
                // Swap pointers
                tmp = entries[j];
                entries[j] = entries[j + 1];
                entries[j + 1] = tmp;
            }
        }
    }
}


blkcnt_t get_block_size(const char *path) {
    struct stat st;

    if (lstat(path, &st) != 0) {
        perror("lstat");
        exit(1);
    }
    return st.st_blocks / 2;
}


bool is_special_dir(const char *path) {
    return !strcmp(path, ".") || !strcmp(path, "..") || !strcmp(path, ".git");
}


int ft_ls(const char *path) {
    _print_max_len print_max_len = {0};
    DIR *dir;

    if (options.is_recursive && !strcmp(path, ".")) {
        printf(".:\n");
    }

    if (is_regular_file(path)) {
        print_regular_file(path, NULL);
        return 0;
    }

    dir = opendir(path);

    if (!dir) {
        perror(path);
        return 1;
    }

    unsigned int entries_number = 0;
    unsigned int dir_number = 0;
    blkcnt_t     total_blocks = 0;
    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        entries_number += 1;
        char *total_path = concat(path, entry->d_name);
        if (!is_special_dir(entry->d_name))
            total_blocks += get_block_size(total_path);
        if (!is_regular_file(total_path)) {
            dir_number += 1;
        }
        get_max_line_length(total_path, &print_max_len);
        free(total_path);
    }


    if (options.format == FORMAT_LONG)
        printf("total %lld\n", (long long)total_blocks);

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
            // if (!is_regular_file(comp_path) && !is_special_dir(comp_path)) {
            if (!is_regular_file(comp_path) && !is_special_dir(entries[i]->d_name)) {
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
            print_regular_file(complete_path, &print_max_len);
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
            print_regular_file(complete_path, &print_max_len);
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
    options.format = FORMAT_LONG;

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
