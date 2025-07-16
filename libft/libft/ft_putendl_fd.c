/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:13:52 by bperraud          #+#    #+#             */
/*   Updated: 2021/12/18 14:42:59 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_putendl_fd(char *s, int fd)
{
	size_t	size;

	size = 0;
	if (!s)
		return (0);
	while (*s)
		size += write(fd, s++, 1);
	size += write(fd, "\n", 1);
	return (size);
}
