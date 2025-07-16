/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 02:42:51 by bperraud          #+#    #+#             */
/*   Updated: 2021/11/17 11:32:15 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

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
