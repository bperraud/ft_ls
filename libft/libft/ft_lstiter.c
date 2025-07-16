/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 01:02:09 by bperraud          #+#    #+#             */
/*   Updated: 2022/01/16 01:11:16 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void*))
{
	if (lst && f)
	{
		while (lst->next)
		{
			(f)(lst->content);
			lst = lst->next;
		}
		(f)(lst->content);
	}
}
