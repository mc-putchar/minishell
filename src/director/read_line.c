/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 17:36:35 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/07 13:32:24 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete(t_cmdline *cmdl)
{
	CLEAR_REST();
	ft_memcpy(&cmdl->buff[cmdl->i], &cmdl->buff[cmdl->i + 1], \
		cmdl->size - cmdl->i);
	cmdl->buff[cmdl->size] = 0;
	write(1, &cmdl->buff[cmdl->i], cmdl->size - cmdl->i);
	(cmdl->size)--;
	if (cmdl->size > cmdl->i)
		MOVE_LEFT(cmdl->size - cmdl->i);
}

static void	csi_handler(int ret, t_cmdline *cmdl, char *prompt)
{
	if (ret == ARROW_UP)
		ctrl_up_history(cmdl, prompt);
	else if (ret == ARROW_DOWN)
		ctrl_down_history(cmdl, prompt);
	else if (ret == ARROW_RIGHT && cmdl->i < cmdl->size && ++(cmdl->i))
		MOVE_RIGHT(1);
	else if (ret == ARROW_LEFT && cmdl->i > 0 && (cmdl->i)--)
		MOVE_LEFT(1);
	else if (ret == DELETE && cmdl->i < cmdl->size)
		delete(cmdl);
	else if (ret == HOME && cmdl->i > 0)
	{
		MOVE_LEFT(cmdl->i);
		cmdl->i = 0;
	}
	else if (ret == END && cmdl->i < cmdl->size)
	{
		MOVE_RIGHT(cmdl->size - cmdl->i);
		cmdl->i = cmdl->size;
	}
}

static void	check_control(int ret, t_cmdline *cmdl, char *prompt)
{
	if (ret == CTRL_D && !cmdl->size)
		gtfo(cmdl, EXIT_SUCCESS, NULL);
	else if (ret == CTRL_C)
	{
		ft_printf("^C\n");
		reset_cmd_line(cmdl, prompt);
		if (!prompt)
			flush_history(cmdl);
	}
	else if (ret == CTRL_L)
	{
		CLEAR_SCREEN();
		MOVE_HOME();
		if (print_prompt(prompt))
			ft_perror("print_prompt");
		ft_printf("%s", cmdl->buff);
		MOVE_LEFT(cmdl->size - cmdl->i);
		if (!cmdl->size)
			ft_printf(" ");
		else if (cmdl->i == cmdl->size)
			MOVE_RIGHT(1);
	}
	else if (ret == BACKSPACE && cmdl->i > 0)
	{
		(cmdl->i)--;
		MOVE_LEFT(1);
		delete(cmdl);
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
		ft_memmove(&cmdl->buff[cmdl->i + 1], &cmdl->buff[cmdl->i], \
			cmdl->size - cmdl->i);
		cmdl->buff[(cmdl->i)++] = ret;
		write(1, &cmdl->buff[cmdl->i - 1], cmdl->size + 1 - cmdl->i);
		MOVE_LEFT(cmdl->size - cmdl->i);
	}
}

char	*read_line(char *prompt)
{
	t_cmdline	cmdl;
	int			ret;
	ssize_t		read_ret;

	(void)prompt;
	reset_cmd_line(&cmdl, prompt);
	if (!prompt)
		g_shell.cmdl = &cmdl;
	while (true)
	{
		ret = 0;
		read_ret = read(STDIN_FILENO, &ret, 4);
		if (read_ret == -1)
			return (NULL);
		if (ft_isprint(ret))
			insert_input(ret, &cmdl);
		else if ((ret & 0xff) == ESCAPE)
			csi_handler(ret, &cmdl, prompt);
		else if ((ret == '\n' || ret == '\r'))
		{
			cmdl.buff[cmdl.size] = 0;
			if (!prompt)
				flush_history(&cmdl);
			ft_printf("\r\n");
			return (ft_strdup(cmdl.buff));
		}
		else if (ft_isascii(ret))
			check_control(ret, &cmdl, prompt);
	}
}
