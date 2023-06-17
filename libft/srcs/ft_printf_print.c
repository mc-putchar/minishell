/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:58:18 by dlu               #+#    #+#             */
/*   Updated: 2023/05/23 11:32:38 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Handle the specifier 'c' and '%'. */
void	print_char(char c, int *count, t_format format)
{
	if (!format.minus)
		*count += print_padding(format.padding, format.width - 1);
	write(1, &c, 1);
	(*count)++;
	if (format.minus)
		*count += print_padding(format.padding, format.width - 1);
}

/* Handle the specifier 's', and the number portion of 'diuxX'. */
int	print_str(char *s, int *count, t_format format)
{
	int	len;
	int	i;

	if (!s && !format.dot && print_str(NULL_STR, count, format))
		return (0);
	else if (!s && format.precision >= 6 && print_str(NULL_STR, count, format))
		return (0);
	len = ft_strlenf(s, format);
	if (!format.minus)
		*count += print_padding(format.padding, format.width - len);
	i = -1;
	while (++i < len)
		write(1, &s[i], 1);
	*count += len;
	if (format.minus)
		*count += print_padding(format.padding, format.width - len);
	return (1);
}

/* Handle the specifier 'diuxX'. */
void	print_nbr(t_ll n, const char *base, int *count, t_format format)
{
	format.nbr = n;
	parse_nbr(format.nbr, base, &format);
	print_str(format.num, count, format);
	free(format.num);
}

/* Handle the specifier 'p'. */
void	print_ptr(void *p, int *count, t_format format)
{
	if (!p && print_str(NULL_PTR, count, format))
		return ;
	format.nbr = (t_ll) p;
	parse_nbr(format.nbr, HEXL, &format);
	print_str(format.num, count, format);
	free(format.num);
}

/* Print the next argument based on its specifier. */
void	print_arg(va_list *args, int *count, t_format format)
{
	if (format.type == 'c')
		print_char(va_arg(*args, int), count, format);
	else if (format.type == 's')
		print_str(va_arg(*args, char *), count, format);
	else if (format.type == 'p')
		print_ptr(va_arg(*args, void *), count, format);
	else if (format.type == 'd' || format.type == 'i')
		print_nbr((t_ll) va_arg(*args, int), DEC, count, format);
	else if (format.type == 'x')
		print_nbr((t_ll) va_arg(*args, t_ui), HEXL, count, format);
	else if (format.type == 'X')
		print_nbr((t_ll) va_arg(*args, t_ui), HEXU, count, format);
	else if (format.type == 'u')
		print_nbr((t_ll) va_arg(*args, t_ui), DEC, count, format);
	else if (format.type == '%')
		print_char('%', count, format);
}
