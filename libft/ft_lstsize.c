/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 01:45:42 by fgonzale          #+#    #+#             */
/*   Updated: 2022/12/14 02:09:58 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	elements_count;

	elements_count = 0;
	while (lst != NULL)
	{
		elements_count++;
		lst = lst->next;
	}
	return (elements_count);
}
