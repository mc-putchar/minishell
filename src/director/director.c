/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   director.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 05:26:20 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/08 17:51:53 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: write history to file on exit
void	gtfo(t_cmdline *cmdl, int status, char *msg)
{
	ft_lstclear(&g_shell.hist, free);
	(void) cmdl;
	if (g_shell.tok_head)
		free_token(g_shell.tok_head);
	if (g_shell.ast)
		free_cmd_ast(g_shell.ast);
	ft_strarrfree(g_shell.envp);
	if (!msg)
		ft_dprintf(STDOUT_FILENO, "\r\nbyeee!\r\n");
	else
		ft_dprintf(STDOUT_FILENO, "%s\r\n", msg);
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
		ft_printf("%s%s", MISH, PROMPT);
	cmdl->hist = NULL;
}

int	do_stuff(void)
{
	char		*line;
	t_termios	term_backup;

	ft_bzero(&term_backup, sizeof(term_backup));
	g_shell.term_backup = &term_backup;
	while (true)
	{
		if (setup_terminal(&term_backup))
			return (ft_dprintf(STDERR_FILENO, MISH": error: %s\n", \
				strerror(errno)));
		line = read_line(NULL);
		reset_terminal(&term_backup);
		if (!line)
			return (ft_dprintf(STDERR_FILENO, MISH": error: read_line\n"));
		parse_execute(line);
	}
}

int	director(void)
{
	if (init_history())
		return (EXIT_FAILURE);
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
		return (ENOTTY);
	else if (do_stuff())
		ft_dprintf(STDERR_FILENO, MISH": error: do_stuff\n");
	return (EXIT_SUCCESS);
}
