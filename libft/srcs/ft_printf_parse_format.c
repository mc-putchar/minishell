/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse_format.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:35:33 by dlu               #+#    #+#             */
/*   Updated: 2023/05/23 11:30:26 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Parse the flags in order. */
static void	parse_flags(char **s, t_format *format)
{
	while (**s == '#' && (*s)++)
		format->hash = 1;
	while (**s == '-' && (*s)++)
		format->minus = 1;
	while (**s == '+' && (*s)++)
		format->plus = 1;
	while (**s == ' ' && (*s)++)
		format->space = 1;
	while (**s == '0' && (*s)++)
		format->zero = 1;
	if (format->plus)
		format->space = 0;
	if (format->minus)
		format->zero = 0;
}

/* Parse the width of the format. */
static void	parse_width(char **s, va_list *args, t_format *format)
{
	if (**s == '*')
	{
		format->width = va_arg(*args, int);
		(*s)++;
		return ;
	}
	while (**s >= '0' && **s <= '9')
	{
		format->width = (format->width * 10) + **s - '0';
		(*s)++;
	}
}

/* Parse the precision of the format. */
static void	parse_precision(char **s, va_list *args, t_format *format)
{
	if (**s == '.')
	{
		format->dot = 1;
		(*s)++;
	}
	if (**s == '*')
	{
		format->precision = va_arg(*args, int);
		if (format->precision < 0)
			format->precision = 0;
		(*s)++;
		return ;
	}
	while (**s >= '0' && **s <= '9')
	{
		format->precision = (format->precision * 10) + **s - '0';
		(*s)++;
	}
}

/* Parse the format and set its parameters. */
void	parse_format(char **s, va_list *args, t_format *format)
{
	parse_flags(s, format);
	parse_width(s, args, format);
	parse_precision(s, args, format);
	format->type = **s;
	if (**s == 'p' || **s == 'x' || **s == 'X')
		format->base = 16;
	if (**s == 'd' || **s == 'i')
		format->signed_nbr = 1;
	if (format->zero)
		format->padding = '0';
	if (format->dot && format->zero)
		format->padding = ' ';
	(*s)++;
}
