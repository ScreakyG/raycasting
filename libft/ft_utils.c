/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 01:02:45 by fgonzale          #+#    #+#             */
/*   Updated: 2022/12/22 22:09:42 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *str)
{
	unsigned int	i;
	unsigned int	print_len;

	if (!str)
		return (write(1, "(null)", 6));
	i = 0;
	print_len = 0;
	while (str[i])
		print_len += write(1, &str[i++], 1);
	return (print_len);
}

int	ft_putnbr_decimal(int nb, unsigned long base, const char format)
{
	unsigned int	print_len;
	long			n;

	n = nb;
	print_len = 0;
	if (nb < 0)
	{
		print_len += ft_putchar('-');
		n *= -1;
	}
	print_len += ft_putnbr_base(n, base, format);
	return (print_len);
}

int	ft_putnbr_base(unsigned long n, unsigned long base, const char format)
{
	unsigned int	print_len;

	print_len = 0;
	if (n == 0)
		return (print_len += ft_putchar('0'));
	if (n > 0)
	{
		if (n >= base)
			print_len += ft_putnbr_base((n / base), base, format);
		if (format == 'X')
			print_len += write(1, &"0123456789ABCDEF"[n % base], 1);
		else
			print_len += write(1, &"0123456789abcdef"[n % base], 1);
	}
	return (print_len);
}

int	ft_ptr(unsigned long ptr, unsigned long base, const char format)
{
	unsigned int	print_len;

	if (!ptr)
		return (ft_putstr("(nil)"));
	print_len = 0;
	print_len += write(1, "0x", 2);
	print_len += ft_putnbr_base(ptr, base, format);
	return (print_len);
}
