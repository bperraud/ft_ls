#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <unistd.h>

#include "libft/libft/libft.h"

int is_regular_file(const char *path) {
    struct stat st;
    if (stat(path, &st) == 0) {
        return S_ISREG(st.st_mode);
    } else {
        return -1;
    }
}

static char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

const char* path_basename(const char *path) {
    const char *base;

    base = ft_strrchr(path, '/');
    if (base) {
        return base + 1;
    } else {
        return path;
    }
}

char *concat(const char *s1, const char *s2) {
    size_t len1 = ft_strlen(s1);
    size_t len2 = ft_strlen(s2);
    char *result = malloc(len1 + len2 + 2);
    if (!result) return NULL;
    ft_strcpy(result, s1);
    result[len1] = '/';
    result[len1 + 1] = '\0';
    strcat(result, s2);
    return result;
}
