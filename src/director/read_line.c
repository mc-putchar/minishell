/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 17:36:35 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/15 02:59:43 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	csi_handler(int ret, t_cmdline *cmdl, char *prompt)
{
	if (ret == ARROW_UP)
		ctrl_up_history(cmdl, prompt);
	else if (ret == ARROW_DOWN)
		ctrl_down_history(cmdl, prompt);
	else if (ret == ARROW_RIGHT && cmdl->i < cmdl->size && ++(cmdl->i))
		move_right(1);
	else if (ret == ARROW_LEFT && cmdl->i > 0 && (cmdl->i)--)
		move_left(1);
	else if (ret == DELETE && cmdl->i < cmdl->size)
		delete(cmdl);
	else if (ret == HOME && cmdl->i > 0)
	{
		move_left(cmdl->i);
		cmdl->i = 0;
	}
	else if (ret == END && cmdl->i < cmdl->size)
	{
		move_right(cmdl->size - cmdl->i);
		cmdl->i = cmdl->size;
	}
}

static void	insert_input(int ret, t_cmdline *cmdl)
{
	if (cmdl->i == cmdl->size)
	{
		cmdl->buff[(cmdl->i)++] = ret;
		write(1, &cmdl->buff[cmdl->i - 1], 1);
		(cmdl->size)++;
	}
	else
	{
		(cmdl->size)++;
		(void)ft_memmove(&cmdl->buff[cmdl->i + 1], &cmdl->buff[cmdl->i], \
			cmdl->size - cmdl->i);
		cmdl->buff[(cmdl->i)++] = ret;
		write(1, &cmdl->buff[cmdl->i - 1], cmdl->size + 1 - cmdl->i);
		move_left(cmdl->size - cmdl->i);
	}
}

static int	ctrl_switch(int ret, t_cmdline *cmdl, char *prompt)
{
	if (ft_isprint(ret))
		insert_input(ret, cmdl);
	else if ((ret & 0xff) == ESCAPE)
		csi_handler(ret, cmdl, prompt);
	else if (ret == BACKSPACE && cmdl->i > 0)
		backspace(cmdl);
	else if (ft_isascii(ret))
		return (check_control(ret, cmdl, prompt));
	return (0);
}

char	*read_line(char *prompt)
{
	t_cmdline	cmdl;
	int			ret;
	ssize_t		read_ret;

	reset_cmd_line(&cmdl, prompt);
	if (!prompt)
		g_shell.cmdl = &cmdl;
	while (true)
	{
		ret = 0;
		read_ret = read(STDIN_FILENO, &ret, 4);
		if (read_ret == -1)
			return (NULL);
		else if ((ret == '\n' || ret == '\r'))
		{
			cmdl.buff[cmdl.size] = 0;
			if (!prompt)
				(void)flush_history(&cmdl);
			ft_printf("\r\n");
			return (ft_strdup(cmdl.buff));
		}
		else if (ctrl_switch(ret, &cmdl, prompt))
			return (NULL);
	}
}
