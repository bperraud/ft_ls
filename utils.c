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

static int	ft_nbrchar(int n)
{
	int	i;

	i = 1;
	if (n < 0)
	{
		i++;
		while (n < -9)
		{
			n /= 10;
			i++;
		}
	}
	else
	{
		while (n > 9)
		{
			n /= 10;
			i++;
		}
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		size;
	char	*str;
	int		neg;

	neg = 0;
	size = ft_nbrchar(n);
	str = malloc((size + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[size] = '\0';
	if (n < 0)
	{
		neg = 1;
		str[0] = '-';
	}
	while (size-- > neg)
	{
		if (neg)
			str[size] = -(n % 10) + '0';
		else
			str[size] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
