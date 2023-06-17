/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:22:48 by dlu               #+#    #+#             */
/*   Updated: 2023/05/23 11:22:52 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	if (!dst && !src)
		return (NULL);
	if (src < dst)
		while (len--)
			((t_uc *) dst)[len] = ((t_uc *) src)[len];
	else
		while (++i <= len)
			((t_uc *) dst)[i - 1] = ((t_uc *) src)[i - 1];
	return (dst);
}
