#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "libft/libft/libft.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

// main

typedef struct struct_print_len {
    size_t uid;
    size_t gid;
    size_t hard_links;
    size_t size;
    size_t datetime;
} _print_max_len;

typedef struct struct_options {
    bool is_long_format;
    bool is_reversed;
    bool is_recursive;
    bool is_time_sorted;
    bool include_hidden_files;
} _options;


int is_regular_file(const char *path);
char *join_path(const char *s1, const char *s2);
const char* path_basename(const char *path);
char	*ft_itoa(int n);
size_t	ft_strlen(const char *s);

void safe_lstat(const char* path, struct stat *st);
const char* print_basename(const char *path);
void print_regular_file(const char *path, _print_max_len *print_max_len);
void sort_ascii(struct dirent *entries[], size_t count);
int ft_ls(const char *path);
blkcnt_t get_block_size(const char *path);
