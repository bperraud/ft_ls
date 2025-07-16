/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 22:22:32 by bperraud          #+#    #+#             */
/*   Updated: 2022/01/13 19:19:12 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strncpy(char *dest, const char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static int	ft_is_separator(const char c, const char *charset)
{
	while (*charset)
		if (c == *charset++)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		size;
	const char	*start;
	const char	*end;
	char		*dst;

	if (!s1 || !set)
		return (NULL);
	end = s1 + ft_strlen(s1) - 1;
	size = 0;
	start = s1;
	while (*start && ft_is_separator(*start, set))
	{
		start++;
		size += 1;
	}
	if (ft_strlen(s1) - size == 0)
		return (ft_strdup(""));
	while (ft_is_separator(*end--, set))
			size += 1;
	dst = malloc((ft_strlen(s1) - size + 1) * sizeof (char));
	if (!dst)
		return (NULL);
	ft_strncpy(dst, start, ft_strlen(s1) - size);
	return (dst);
}
