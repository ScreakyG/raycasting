/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 04:02:40 by fgonzale          #+#    #+#             */
/*   Updated: 2022/12/14 04:40:53 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*next;

	temp = *lst;
	if (del && *lst)
	{
		while (temp != NULL)
		{
			next = temp->next;
			ft_lstdelone(temp, del);
			temp = next;
		}
	}
	*lst = NULL;
}
