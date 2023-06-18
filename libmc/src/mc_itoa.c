/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mc_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:34:55 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/19 00:12:00 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmc.h"

static int	count_digits(int n)
{
	int	d;

	d = 0;
	if (n < 1)
		++d;
	while (n)
	{
		n /= 10;
		++d;
	}
	return (d);
}

static int	count_udigits(unsigned int n)
{
	int	d;

	d = 0;
	if (!n)
		return (1);
	while (n)
	{
		n /= 10;
		++d;
	}
	return (d);
}

char	*mc_itoa(int n)
{
	char	*num;
	int		digits;
	int		neg;

	digits = count_digits(n);
	num = malloc(digits + 1);
	if (!num)
		return (NULL);
	num[digits] = 0;
	neg = 1;
	if (!n)
		num[0] = '0';
	else if (n < 0)
	{
		num[0] = '-';
		neg = -1;
	}
	while (n && digits--)
	{
		num[digits] = n % 10 * neg + '0';
		n /= 10;
	}
	return (num);
}

char	*mc_uitoa(unsigned int n)
{
	char	*num;
	int		digits;

	digits = count_udigits(n);
	num = malloc(digits + 1);
	if (!num)
		return (NULL);
	num[digits] = 0;
	if (!n)
		num[0] = '0';
	while (n && digits--)
	{
		num[digits] = n % 10 + '0';
		n /= 10;
	}
	return (num);
}
