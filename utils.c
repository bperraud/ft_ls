#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>


int is_regular_file(const char *path) {
    struct stat st;
    if (stat(path, &st) == 0) {
        return S_ISREG(st.st_mode);
    } else {
        perror("stat");
        return 0;
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
