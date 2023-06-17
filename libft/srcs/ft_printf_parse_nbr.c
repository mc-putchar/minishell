/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse_nbr.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:22:14 by dlu               #+#    #+#             */
/*   Updated: 2023/05/23 11:30:58 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Return the length of the nbr, excluding '-'. */
static int	nbr_len(t_ll n, t_format *format)
{
	int	len;

	len = 0;
	if (n == 0)
		return (++len);
	while (format->signed_nbr && n != 0 && ++len)
		n /= format->base;
	while (!format->signed_nbr && n != 0 && ++len)
		n = (t_ull) n / format->base;
	return (len);
}

/* Return the length of the nbr string, excluding '\0'. */
static int	nbr_strlen(t_ll n, t_format *format)
{
	int	len;

	len = nbr_len(n, format);
	if (format->dot && !format->precision && n == 0)
		return (0);
	if (len < format->precision)
		len = format->precision;
	if (format->signed_nbr && (n < 0 || format->plus || format->space))
		++len;
	if ((((format->type == 'x' || format->type == 'X') && format->hash)
			|| format->type == 'p') && n != 0)
		len += 2;
	return (len);
}

/* Handle the prefixes (+/-/ /0x/0X) and the precision padding. */
static void	nbr_prefix(t_ll n, t_format *format, int len)
{
	if (format->signed_nbr)
	{
		if (n < 0)
			format->num[0] = '-';
		else if (format->plus)
			format->num[0] = '+';
		else if (format->space)
			format->num[0] = ' ';
	}
	if ((((format->type == 'x' || format->type == 'X') && format->hash)
			|| format->type == 'p') && n != 0)
	{
		format->num[0] = '0';
		if (format->type == 'X')
			format->num[1] = 'X';
		else
			format->num[1] = 'x';
	}
	while (--len >= 0 && !format->num[len])
		format->num[len] = '0';
}

/* Handle the co-occurance of flag '0' and prefix(+/-/ ). */
static void	nbr_flag_zero(t_format *format)
{
	if (!format->dot)
	{
		if (format->zero && format->signed_nbr
			&& (format->nbr < 0 || format->plus || format->space))
			format->precision = format->width - 1;
		if (format->zero && !format->signed_nbr)
			format->precision = format->width;
	}
}

/* Load the number into string and store in the format to print later. */
void	parse_nbr(t_ll n, const char *base, t_format *format)
{
	int	len;

	nbr_flag_zero(format);
	len = nbr_strlen(n, format) + 1;
	format->num = ft_calloc(len, sizeof(char));
	if (!format->num)
		return ;
	format->num[--len] = '\0';
	while (format->signed_nbr && n != 0 && --len >= 0)
	{
		if (n > 0)
			format->num[len] = base[n % format->base];
		else
			format->num[len] = base[-(n % format->base)];
		n /= format->base;
	}
	while (!format->signed_nbr && n != 0 && --len >= 0)
	{
		format->num[len] = base[(t_ull) n % format->base];
		n = (t_ull) n / format->base;
	}
	nbr_prefix(format->nbr, format, len);
}
