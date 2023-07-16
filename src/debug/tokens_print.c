/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:00:49 by dlu               #+#    #+#             */
/*   Updated: 2023/07/16 16:57:08 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokens_print(t_token *start)
{
	int	i;

	i = 0;
	while (start && ++i)
	{
		ft_printf("token %d: %s\n", i, start->value);
		start = start->next;
	}
}
