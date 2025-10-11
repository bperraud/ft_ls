#include "header.h"
#include "libft/libft/libft.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>
#include <time.h>

#include "libft/ft_printf.h"

_options options;
bool    first_arg;


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

    ft_printf("%s ", perms);
}


char * get_ctime_ls_format(time_t mod_time) {
    char *full;

    full = ctime(&mod_time);
    full[16] = '\0';
    return full + 4;
}

void string_format(size_t len, size_t max_len) {
    char a = ' ';
    for (size_t i = len; i < max_len; i++) {
        write(0, &a, 1);
    }
}

void print_symlink(const char* path) {
    char buffer[ft_strlen(path_basename(path)) + 1];
    ssize_t len = readlink(path, buffer, sizeof(buffer) - 1);
    buffer[len] = '\0';
    ft_printf(" -> %s", buffer);
}

void print_regular_file(const char *path, _print_max_len *print_max_len) {
    struct stat st;
    const char *file_name;
    char *st_size_str;
    char *st_nlink_str;

    if (options.is_long_format) {
        safe_lstat(path, &st);
        print_permissions(st.st_mode);
        st_nlink_str = ft_itoa(st.st_nlink);
        string_format(ft_strlen(st_nlink_str), print_max_len->hard_links);
        ft_printf("%u ", (unsigned int)st.st_nlink);
        ft_printf("%s ", getpwuid(st.st_uid)->pw_name);
        string_format(ft_strlen(getpwuid(st.st_uid)->pw_name), print_max_len->uid);
        ft_printf("%s ", getgrgid(st.st_gid)->gr_name);
        string_format(ft_strlen(getgrgid(st.st_gid)->gr_name), print_max_len->gid);
        st_size_str = ft_itoa(st.st_size);
        string_format(ft_strlen(st_size_str), print_max_len->size);
        free(st_size_str);
        free(st_nlink_str);
        ft_printf("%d ", st.st_size);
        ft_printf("%s ", get_ctime_ls_format(st.st_mtime));
    }
    file_name = path_basename(path);
    ft_printf("%s", file_name);

    if (options.is_long_format && S_ISLNK(st.st_mode))
        print_symlink(path);

    ft_printf("\n");
}


void get_max_line_length(const char *path, _print_max_len *print_max_len) {
    struct stat     st;
    char *          st_size_str;
    char *          st_nlink_str;

    safe_lstat(path, &st);
    st_nlink_str = ft_itoa(st.st_nlink);
    print_max_len->hard_links = MAX(ft_strlen(st_nlink_str), print_max_len->hard_links);
    print_max_len->uid = MAX(ft_strlen(getpwuid(st.st_uid)->pw_name), print_max_len->uid);
    print_max_len->gid = MAX(ft_strlen(getgrgid(st.st_gid)->gr_name), print_max_len->gid);
    st_size_str = ft_itoa(st.st_size);
    print_max_len->size = MAX(ft_strlen(st_size_str), print_max_len->size);
    print_max_len->datetime = MAX(ft_strlen(get_ctime_ls_format(st.st_mtime)), print_max_len->datetime);
    free(st_size_str);
    free(st_nlink_str);
}

void sort_ascii(struct dirent *entries[], size_t count) {
    struct dirent *tmp;

    for (size_t i = 0; i < count - 1; i++) {
        for (size_t j = 0; j < count - i - 1; j++) {
            if (ft_strcmp(entries[j]->d_name, entries[j + 1]->d_name) > 0) {
                // Swap pointers
                tmp = entries[j];
                entries[j] = entries[j + 1];
                entries[j + 1] = tmp;
            }
        }
    }
}

void sort_time(struct dirent *entries[], size_t count, const char *path) {
    struct dirent *tmp;
    char *complete_i_path;
    char *complete_j_path;
    struct stat ist;
    struct stat jst;
    time_t i_time;
    time_t j_time;

    for (size_t i = 0; i < count - 1; i++) {
        for (size_t j = 0; j < count - i - 1; j++) {
            complete_i_path = join_path(path, entries[j]->d_name);
            complete_j_path = join_path(path, entries[j + 1]->d_name);

            safe_lstat(complete_i_path, &ist);
            i_time = ist.st_mtime;
            safe_lstat(complete_j_path, &jst);
            j_time = jst.st_mtime;
            if (i_time == j_time) {
                if (ft_strcmp(entries[j]->d_name, entries[j + 1]->d_name) > 0) {
                    tmp = entries[j];
                    entries[j] = entries[j + 1];
                    entries[j + 1] = tmp;
                }
            }
            else if (i_time < j_time) {
                tmp = entries[j];
                entries[j] = entries[j + 1];
                entries[j + 1] = tmp;
            }
            free(complete_i_path);
            free(complete_j_path);
        }
    }
}

bool is_special_dir(const char *path) {
    return !ft_strcmp(path, ".") || !ft_strcmp(path, "..");
}

void print_files_in_folder(int entries_number, struct dirent *entries[], _print_max_len print_max_len, const char *path) {
    ssize_t start;
    ssize_t end;
    ssize_t step;
    if (options.is_reversed) {
        start = entries_number - 1;
        end = -1;
        step = -1;
    }
    else {
        start = 0;
        end = entries_number;
        step = 1;
    }

    for (ssize_t i = start; i != end; i += step) {
        if (!options.include_hidden_files && entries[i]->d_name[0] == '.') {
            free(entries[i]);
            continue;
        }

        char *complete_path = join_path(path, entries[i]->d_name);
        print_regular_file(complete_path, &print_max_len);
        free(entries[i]);
        free(complete_path);
    }
}

int ft_ls(const char *path, unsigned int option_arg) {
    _print_max_len print_max_len = {0};
    DIR *dir;

    if (!first_arg)
        ft_printf("\n");
    else
        first_arg = false;

    if (is_regular_file(path) == -1) {
        write(STDERR_FILENO, "ft_ls: cannot access '", 19);
        write(STDERR_FILENO, path, ft_strlen(path));
        write(STDERR_FILENO, "': ", 3);
        perror(NULL);
        return 1;
    }

    if (is_regular_file(path)) {
        print_regular_file(path, &print_max_len);
        return 0;
    }

    dir = opendir(path);

    if (!dir) {
        write(STDERR_FILENO, "ft_ls: cannot open directory '", 27);
        write(STDERR_FILENO, path, ft_strlen(path));
        write(STDERR_FILENO, "': ", 3);
        perror(NULL);
        return 1;
    }

    unsigned int entries_number = 0;
    unsigned int dir_number = 0;
    blkcnt_t     total_blocks = 0;
    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        entries_number += 1;
        char *total_path = join_path(path, entry->d_name);
        if (!is_regular_file(total_path)) {
            dir_number += 1;
        }
        get_max_line_length(total_path, &print_max_len);
        if (!options.include_hidden_files && entry->d_name[0] == '.') {
            free(total_path);
            continue;
        }
        total_blocks += get_block_size(total_path);
        free(total_path);
    }

    if (options.is_long_format)
        ft_printf("total %d\n", total_blocks);

    closedir(dir);

    struct dirent *entries[entries_number];
    char *dir_entries[dir_number];
    dir = opendir(path);

    int i = 0;
    int dir_index = 0;
    while ((entry = readdir(dir)) != NULL) {
        entries[i] = malloc(sizeof(struct dirent));
        if (entries[i]) {
            ft_memcpy(entries[i], entry, sizeof(struct dirent));
            char *comp_path = join_path(path, entries[i]->d_name);
            if (options.is_recursive && !is_regular_file(comp_path) && !is_special_dir(entries[i]->d_name)) {
                dir_entries[dir_index] = ft_strdup(comp_path);
                dir_index += 1;
            }
            free(comp_path);
            i++;
        }
    }

    closedir(dir);

    if (options.is_time_sorted)
        sort_time(entries, entries_number, path);
    else
        sort_ascii(entries, entries_number);


    if (option_arg > 1) {
        ft_printf("%s:\n", path);
    }
    
    print_files_in_folder(entries_number, entries, print_max_len, path);

    if (options.is_recursive) {
        for (ssize_t i = 0; i < dir_index; i++) {
            ft_ls(dir_entries[i], option_arg);
            free(dir_entries[i]);
        }
    }

    return 0;
}

_options parse(int argc, char **argv);

int start(int argc, char **argv) {

    options = parse(argc, argv);

    int program_exit_code;
    int ft_exit_code;
    int option_arg = 0;
    first_arg = true;

    if (argc < 2)
        return ft_ls(".", option_arg);
    for (int i = 1; i < argc; i++) {
        if (argv[i] == NULL) {
            option_arg += 1;
            continue;
        }
        ft_exit_code = ft_ls(argv[i], argc - 1);
        program_exit_code = MAX(program_exit_code, ft_exit_code);
    }
    if (option_arg == argc - 1)
        return ft_ls(".", option_arg);
    return program_exit_code;
}

int main(int argc, char **argv) {
    return start(argc, argv);
}
