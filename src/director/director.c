/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   director.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 05:26:20 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/18 22:52:49 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	gtfo(struct termios *term_backup, char *prompt)
{
	free(prompt);
	mc_dprintf(STDOUT_FILENO, "\r\nbyeee!\r\n");
	reset_terminal(term_backup);
	exit(EXIT_SUCCESS);
}

void	reset_cmd_line(char *prompt, char *buff, int *i)
{
	mc_dprintf(STDOUT_FILENO, "\r\n%s", prompt);
	ft_bzero(buff, BUFSIZ);
	*i = 0;
}

int	director(int ac, char **av, char **envp)
{
	struct termios	term_backup;

	(void)ac;
	(void)av;
	(void)envp;
	if (init_shell())
		return (EXIT_FAILURE);
	if (setup_terminal(&term_backup))
		return (mc_dprintf(STDERR_FILENO, "Error: setup_terminal\n"));
	if (do_stuff(&term_backup))
		mc_dprintf(STDERR_FILENO, "Error: do_stuff\n");
	reset_terminal(&term_backup);
	return (EXIT_SUCCESS);
}
