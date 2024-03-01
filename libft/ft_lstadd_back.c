/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 02:45:25 by fgonzale          #+#    #+#             */
/*   Updated: 2022/12/14 04:41:21 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*previous_last;

	if (new != NULL)
	{
		if (*lst == NULL)
		{
			*lst = new;
			return ;
		}
		previous_last = ft_lstlast(*lst);
		previous_last->next = new;
	}
}
