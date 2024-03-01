/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 00:17:38 by fgonzale          #+#    #+#             */
/*   Updated: 2023/01/20 17:56:08 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_format(const char format, va_list list)
{
	unsigned int	print_len;

	print_len = 0;
	if (format == 'c')
		print_len += ft_putchar(va_arg(list, int));
	else if (format == 's')
		print_len += ft_putstr(va_arg(list, char *));
	else if (format == 'd' || format == 'i')
		print_len += ft_putnbr_decimal(va_arg(list, int), 10, format);
	else if (format == 'x' || format == 'X')
		print_len += ft_putnbr_base(va_arg(list, unsigned int), 16, format);
	else if (format == 'p')
		print_len += ft_ptr((unsigned long)va_arg(list, void *), 16, format);
	else if (format == 'u')
		print_len += ft_putnbr_base(va_arg(list, unsigned int), 10, format);
	else if (format == '%')
		print_len += ft_putchar('%');
	return (print_len);
}

int	ft_printf(const char *str, ...)
{
	unsigned int	print_len;
	unsigned int	i;
	va_list			list;

	print_len = 0;
	i = 0;
	va_start(list, str);
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '%' && str[i + 1])
		{
			print_len += ft_format(str[i + 1], list);
			i++;
		}
		else
			print_len += ft_putchar(str[i]);
		i++;
	}
	va_end(list);
	return (print_len);
}
