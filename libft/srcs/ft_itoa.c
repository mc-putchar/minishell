/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:18:44 by dlu               #+#    #+#             */
/*   Updated: 2023/05/23 12:28:13 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define INT_MIN_LEN	12
#define BASE		10

/* Return the length of itoa string, including the '\0'. */
static size_t	ft_itoa_len(int n)
{
	size_t	len;

	len = 1;
	if (n == 0)
		return (++len);
	if (n == INT_MIN)
		return (INT_MIN_LEN);
	if (n < 0 && ++len)
		n = -n;
	while (n > 0 && ++len)
		n /= BASE;
	return (len);
}

char	*ft_itoa(int n)
{
	char	*num;
	int		len;

	len = (int) ft_itoa_len(n);
	num = (char *) malloc(len * sizeof(char));
	if (!num)
		return (NULL);
	if (n < 0)
		num[0] = '-';
	num[--len] = '\0';
	while (--len >= 0 && num[len] != '-')
	{
		if (n > 0)
			num[len] = n % BASE + '0';
		else
			num[len] = -(n % BASE) + '0';
		n /= BASE;
	}
	return (num);
}
