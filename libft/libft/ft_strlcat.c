/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 02:42:51 by bperraud          #+#    #+#             */
/*   Updated: 2021/11/17 11:32:15 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	n;
	size_t	j;
	size_t	i;

	j = 0;
	i = ft_strlen(dst);
	n = ft_strlen(src);
	if (dstsize <= i)
		n += dstsize;
	else
		n += i;
	while (src[j] && i + 1 < dstsize)
		dst[i++] = src[j++];
	if (j)
		dst[i] = '\0';
	return (n);
}
