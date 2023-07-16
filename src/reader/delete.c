/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 21:21:54 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/16 19:27:08 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete(t_cmdline *cmdl)
{
	clear_to_line_end();
	--(cmdl->size);
	ft_memcpy(&cmdl->buff[cmdl->i], &cmdl->buff[cmdl->i + 1], \
		cmdl->size - cmdl->i);
	cmdl->buff[cmdl->size] = 0;
	write(1, &cmdl->buff[cmdl->i], cmdl->size - cmdl->i + 1);
	if (cmdl->size > cmdl->i)
		move_left(cmdl->size - cmdl->i);
}

void	backspace(t_cmdline *cmdl)
{
	if (cmdl->i > 0)
	{
		(cmdl->i)--;
		move_left(1);
		delete(cmdl);
	}
}
