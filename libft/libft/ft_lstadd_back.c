/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 02:42:51 by bperraud          #+#    #+#             */
/*   Updated: 2021/11/17 11:32:15 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*list;

	if (!*alst)
	{
		*alst = new;
		return ;
	}
	list = *alst;
	while (list->next)
		list = list->next;
	list->next = new;
}
