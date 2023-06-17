/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:07:14 by dlu               #+#    #+#             */
/*   Updated: 2023/05/23 12:27:32 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BASE	10

int	ft_atoi(const char *str)
{
	int	num;
	int	neg;

	num = 0;
	neg = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-' && ++str)
		neg = -1;
	while ((*str >= '0' && *str <= '9') && ++str)
		num = num * BASE + (*(str - 1) - '0');
	return (neg * num);
}
