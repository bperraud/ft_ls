/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:13:52 by bperraud          #+#    #+#             */
/*   Updated: 2021/12/18 14:42:59 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_putnbr_fd(int nb, int fd)
{
	unsigned int	nbr;
	size_t			size;

	size = 0;
	if (nb < 0)
	{
		size += ft_putchar_fd('-', fd);
		nbr = (nb * -1);
	}
	else
		nbr = nb;
	if (nbr >= 10)
		size += ft_putnbr_fd(nbr / 10, fd);
	size += ft_putchar_fd((char)(nbr % 10 + '0'), fd);
	return (size);
}
