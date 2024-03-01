/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:42:33 by francois          #+#    #+#             */
/*   Updated: 2022/12/13 22:59:42 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	gauchetodroite(size_t n, char *ptrdest, char *ptrsrc)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		ptrdest[i] = ptrsrc[i];
		i++;
	}
}

static void	droitetogauche(size_t n, char *ptrdest, char *ptrsrc)
{
	while (n > 0)
	{
		ptrdest[n - 1] = ptrsrc[n - 1];
		n--;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*ptrdest;
	char	*ptrsrc;

	ptrdest = (char *)dest;
	ptrsrc = (char *)src;
	if (!dest && !src)
		return (NULL);
	if (dest > src)
		droitetogauche(n, ptrdest, ptrsrc);
	else
		gauchetodroite(n, ptrdest, ptrsrc);
	return (dest);
}
