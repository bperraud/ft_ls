/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 20:38:11 by bperraud          #+#    #+#             */
/*   Updated: 2022/01/15 20:38:15 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*cdst;
	const char	*csrc;

	cdst = dst;
	csrc = src;
	if (!cdst && !csrc)
		return (NULL);
	while (n--)
		*cdst++ = *csrc++;
	return (dst);
}
