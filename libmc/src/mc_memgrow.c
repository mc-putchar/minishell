/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mc_memgrow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 03:45:34 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/18 06:32:56 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmc.h"

void	*mc_memgrow(void *ptr, size_t old_size, size_t new_size)
{
	void	*new;

	new = malloc(new_size);
	if (!new)
		return (NULL);
	if (ptr && new_size > old_size)
		new = ft_memcpy(new, ptr, old_size);
	return (free(ptr), new);
}
