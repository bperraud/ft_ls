/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:13:52 by bperraud          #+#    #+#             */
/*   Updated: 2021/12/18 14:42:59 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	uc;

	uc = c;
	while (*s)
	{
		if (*s == uc)
			return ((void *)s);
		s++;
	}
	if (*s == uc)
		return ((void *)s);
	else
		return (NULL);
}
