/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mc_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 22:14:02 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/18 06:18:29 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmc.h"

void	*mc_memccpy(void *dest, const void *src, int c, size_t n)
{
	while (n--)
	{
		*(unsigned char *)dest = *(unsigned char *)src++;
		if (*(unsigned char *)dest++ == c)
			return (dest);
	}
	return (NULL);
}
