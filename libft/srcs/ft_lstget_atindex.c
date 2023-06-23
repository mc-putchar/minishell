/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget_atindex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:49:33 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/20 20:51:10 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstget_atindex(t_list *lst, int index)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = lst;
	while (tmp && i < index)
	{
		tmp = tmp->next;
		i++;
	}
	if (i != index)
		return (NULL);
	return (tmp);
}
