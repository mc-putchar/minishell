/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   director.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 05:26:20 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/16 18:47:20 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	gtfo(t_cmdline *cmdl, int status, char *msg, bool ischild)
{
	if (ischild && g_shell.pids)
		free(g_shell.pids);
	if (g_shell.hist)
		ft_lstclear(&g_shell.hist, free);
	(void) cmdl;
	if (g_shell.tok_head)
		free_token(g_shell.tok_head);
	if (g_shell.ast)
		free_cmd_ast(g_shell.ast);
	ft_strarrfree(g_shell.envp);
	if (!ischild)
	{
		if (!msg)
			ft_dprintf(STDOUT_FILENO, "\r\nbyeee!\r\n");
		else
			ft_dprintf(STDOUT_FILENO, "%s\r\n", msg);
		reset_terminal(g_shell.term_backup);
	}
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

int	director(int ac, char **av)
{
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
		return (run_script(STDIN_FILENO));
	if (ac > 1)
		return (open_script(av[1]));
	if (init_history())
		return (EXIT_FAILURE);
	else if (do_stuff())
		ft_dprintf(STDERR_FILENO, MISH": error: do_stuff\n");
	return (EXIT_SUCCESS);
}
