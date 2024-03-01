/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:42:33 by francois          #+#    #+#             */
/*   Updated: 2022/12/19 02:39:32 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;
	char	*to_find;

	i = 0;
	str = (char *)big;
	to_find = (char *)little;
	if (to_find[i] == '\0')
		return (str);
	if (len > 0)
	{
		while (str[i] != '\0' && i < len)
		{
			j = 0;
			while (str[i + j] && str[i + j] == to_find[j] && i + j < len)
			{
				if (to_find[j + 1] == '\0')
					return (&str[i]);
				j++;
			}
			i++;
		}
	}
	return (0);
}
