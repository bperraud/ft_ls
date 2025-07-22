
#include "header.h"

#include "libft/libft/libft.h"

int is_regular_file(const char *path) {
    struct stat st;
    if (stat(path, &st) == 0) {
        return S_ISREG(st.st_mode);
    } else {
        return -1;
    }
}

void safe_lstat(const char* path, struct stat *st) {
    if (lstat(path, st) != 0) {
        write(STDERR_FILENO, "ls: cannot open '", 17);
        write(STDERR_FILENO, path, ft_strlen(path));
        write(STDERR_FILENO, "': ", 3);
        perror(NULL);
        exit(1);
    }
}

blkcnt_t get_block_size(const char *path) {
    struct stat st;

    safe_lstat(path, &st);
    return st.st_blocks / 2;
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
