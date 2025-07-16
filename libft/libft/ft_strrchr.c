/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 22:09:30 by bperraud          #+#    #+#             */
/*   Updated: 2022/01/16 22:09:34 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*found;
	const char	*p;

	c = (unsigned char) c;
	if (c == '\0')
		return (ft_strchr(s, '\0'));
	found = NULL;
	p = ft_strchr(s, c);
	while (p)
	{
		found = p;
		s = p + 1;
		p = ft_strchr(s, c);
	}
	return ((char *)found);
}
