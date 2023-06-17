/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:58:18 by dlu               #+#    #+#             */
/*   Updated: 2023/05/23 12:10:25 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Reset the format parameters to the initial states. */
static void	reset_format(t_format *format)
{
	format->nbr = 0;
	format->type = 0;
	format->padding = ' ';
	format->num = NULL;
	format->hash = 0;
	format->minus = 0;
	format->plus = 0;
	format->space = 0;
	format->dot = 0;
	format->zero = 0;
	format->width = 0;
	format->precision = 0;
	format->base = 10;
	format->signed_nbr = 0;
}

/* Parse the template string char by char. */
static int	parse(char *s, va_list *args, t_format *format)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s == '%')
		{
			++s;
			reset_format(format);
			parse_format(&s, args, format);
			print_arg(args, &count, *format);
		}
		else
		{
			write(1, s++, 1);
			++count;
		}
	}
	return (count);
}

/* Mimic the system printf function, works with cspdiuxX%. */
int	ft_printf(const char *s, ...)
{
	int			count;
	va_list		args;
	t_format	format;

	reset_format(&format);
	va_start(args, s);
	count = parse((char *) s, &args, &format);
	va_end(args);
	return (count);
}
