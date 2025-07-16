/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 22:06:13 by bperraud          #+#    #+#             */
/*   Updated: 2022/01/16 22:06:16 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*us1;
	const unsigned char	*us2;

	us1 = s1;
	us2 = s2;
	while (n && us1 && us2 && (*us1 == *us2))
	{
		us1++;
		us2++;
		n--;
	}
	if (n)
		return (*us1 - *us2);
	else
		return (0);
}
