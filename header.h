#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int is_regular_file(const char *path);
char *concat(const char *s1, const char *s2);


// main

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


const char* print_basename(const char *path);
void print_regular_file(const char *path);
void sort_ascii(struct dirent *entries[], size_t count);
int ft_ls(const char *path);
