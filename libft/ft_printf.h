/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 22:20:59 by bperraud          #+#    #+#             */
/*   Updated: 2022/02/05 19:43:54 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>

int		ft_printf(const char *args, ...);
size_t	ft_hexa(unsigned long nbr, int option);
size_t	ft_print_conv(char car, va_list args);
size_t	ft_putnbr_fd_unsigned(unsigned int nb, int fd);

#endif
