/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   director.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 05:26:20 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/22 11:35:32 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: write history to file on exit
void	gtfo(t_cmdline *cmdl)
{
	ft_lstclear(&g_shell.hist, free);
	if (cmdl->hist)
		free(cmdl->hist);
	free(cmdl->prompt);
	ft_dprintf(STDOUT_FILENO, "\r\nbyeee!\r\n");
	exit(EXIT_SUCCESS);
}

void	reset_cmd_line(t_cmdline *cmdl)
{
	cmdl->i = 0;
	cmdl->size = 0;
	ft_bzero(cmdl->buff, BUFSIZ);
	ft_dprintf(STDOUT_FILENO, "\r\n%s", cmdl->prompt);
	cmdl->hist = NULL;
}

int	director(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;
	if (init_shell())
		return (EXIT_FAILURE);
	if (do_stuff())
		ft_dprintf(STDERR_FILENO, "Error: do_stuff\n");
	return (EXIT_SUCCESS);
}
