/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 23:16:55 by bperraud          #+#    #+#             */
/*   Updated: 2022/02/05 19:44:13 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

size_t	ft_putnbr_fd_unsigned(unsigned int nb, int fd)
{
	size_t	size;

	size = 0;
	if (nb >= 10)
		size += ft_putnbr_fd(nb / 10, fd);
	size += ft_putchar_fd((char)(nb % 10 + '0'), fd);
	return (size);
}

size_t	ft_hexa(unsigned long nbr, int option)
{
	char	a;
	size_t	size;

	size = 0;
	if (nbr < 16)
	{
		a = "0123456789abcdef"[nbr];
		if (option == 1)
			a = ft_toupper(a);
		size += ft_putchar_fd(a, 1);
	}
	else
	{
		size += ft_hexa(nbr / 16, option);
		size += ft_hexa(nbr % 16, option);
	}
	return (size);
}

size_t	ft_print_conv(char conv, va_list args)
{
	void	*nbr;

	if (conv == 'c')
		return (ft_putchar_fd(va_arg(args, int), 1));
	if (conv == 'd' || conv == 'i')
		return (ft_putnbr_fd(va_arg(args, int), 1));
	if (conv == 'u')
		return (ft_putnbr_fd_unsigned(va_arg(args, unsigned int), 1));
	if (conv == 'x')
		return (ft_hexa(va_arg(args, unsigned int), 0));
	if (conv == 'X')
		return (ft_hexa(va_arg(args, unsigned int), 1));
	if (conv == 'p')
	{
		nbr = va_arg(args, void *);
		ft_putstr_fd("0x", 1);
		return (2 + ft_hexa((unsigned long)(nbr), 0));
	}
	if (conv == 's')
		return (ft_putstr_fd(va_arg(args, char *), 1));
	if (conv == '%')
		return (ft_putchar_fd('%', 1));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		size;

	size = 0;
	va_start(args, format);
	while (*format)
	{		
		if (*format != '%')
			size += write(1, format, 1);
		else
		{
			format++;
			size += ft_print_conv(*format, args);
		}
		format++;
	}
	va_end(args);
	return (size);
}
