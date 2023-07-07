/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   director.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 05:26:20 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/07 10:09:26 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: write history to file on exit
void	gtfo(t_cmdline *cmdl, int status)
{
	ft_lstclear(&g_shell.hist, free);
	(void) cmdl;
	if (g_shell.tok_head)
		free_token(g_shell.tok_head);
	if (g_shell.ast)
		free_cmd_ast(g_shell.ast);
	ft_strarrfree(g_shell.envp);
	ft_dprintf(STDOUT_FILENO, "\r\nbyeee!\r\n");
	reset_terminal(g_shell.term_backup);
	exit(status);
}

void	reset_cmd_line(t_cmdline *cmdl, char *prompt)
{
	cmdl->i = 0;
	cmdl->size = 0;
	cmdl->hist = NULL;
	ft_bzero(cmdl->buff, BUFSIZ);
	if (print_prompt(prompt))
		ft_perror("print_prompt");
	cmdl->hist = NULL;
}

int	director(void)
{
	if (init_history())
		return (EXIT_FAILURE);
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO) || !isatty(STDERR_FILENO))
		return (ENOTTY);
	else if (do_stuff())
		ft_perror("do_stuff");
	return (EXIT_SUCCESS);
}
