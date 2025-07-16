/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:13:52 by bperraud          #+#    #+#             */
/*   Updated: 2022/01/15 17:03:43 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char			*d;
	const char		*s;
	char			*lasts;
	char			*lastd;

	d = dst;
	s = src;
	lasts = (void *) s + (len - 1);
	lastd = d + (len - 1);
	if (d <= s)
		ft_memcpy(dst, src, len);
	else
	{
		while (len-- > 0)
			*lastd-- = *lasts--;
	}
	return (dst);
}
