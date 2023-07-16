/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mission_ctrl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 02:45:49 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/16 19:36:10 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ctrl_exit(t_cmdline *cmdl, char *prompt)
{
	if (prompt && !ft_memcmp(prompt, HERE_PROMPT, ft_strlen(HERE_PROMPT)))
	{
		ft_dprintf(2, "\r\n%s: warning: here-document delimited by end-of-file \
(wanted `EOF')\r\n", MISH);
		return (1);
	}
	return (gtfo(cmdl, EXIT_SUCCESS, NULL, false), 0);
}

static int	ctrl_cancel(t_cmdline *cmdl, char *prompt)
{
	ft_printf("^C\r\n");
	g_shell.status = 130;
	if (prompt)
		return (1);
	reset_cmd_line(cmdl, prompt);
	(void)flush_history(cmdl);
	return (0);
}

int	check_control(int ret, t_cmdline *cmdl, char *prompt)
{
	if (ret == CTRL_D && !cmdl->size)
		return (ctrl_exit(cmdl, prompt));
	else if (ret == CTRL_C && ctrl_cancel(cmdl, prompt))
		return (1);
	else if (ret == CTRL_L)
	{
		clear_terminal();
		move_home();
		if (print_prompt(prompt))
			(void)ft_printf("%s%s", MISH, PROMPT);
		(void)ft_printf("%s", cmdl->buff);
		move_left(cmdl->size - cmdl->i);
		if (!cmdl->size)
			(void)ft_printf(" ");
		else if (cmdl->i == cmdl->size)
			move_right(1);
	}
	return (0);
}
