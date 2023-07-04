/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 17:36:35 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/04 11:28:05 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete(t_cmdline *cmdl)
{
	CLEAR_REST;
	ft_memcpy(&cmdl->buff[cmdl->i], &cmdl->buff[cmdl->i + 1], \
		cmdl->size - cmdl->i);
	cmdl->buff[cmdl->size] = 0;
	write(1, &cmdl->buff[cmdl->i], cmdl->size - cmdl->i);
	(cmdl->size)--;
	if (cmdl->size > cmdl->i)
		MOVE_LEFT(cmdl->size - cmdl->i);
}

void	csi_handler(int ret, t_cmdline *cmdl)
{
	if (ret == ARROW_UP)
		ctrl_up_history(cmdl);
	else if (ret == ARROW_DOWN)
		ctrl_down_history(cmdl);
	else if (ret == ARROW_RIGHT && cmdl->i < cmdl->size && ++(cmdl->i))
		MOVE_RIGHT(1);
	else if (ret == ARROW_LEFT && cmdl->i > 0 && (cmdl->i)--)
		MOVE_LEFT(1);
	else if (ret == DELETE && cmdl->i < cmdl->size)
		delete(cmdl);
}

void	check_control(int ret, t_cmdline *cmdl)
{
	if (ret == CTRL_D && !cmdl->size)
		gtfo(cmdl);
	else if (ret == CTRL_C)
	{
		ft_printf("^C");
		reset_cmd_line(cmdl);
		flush_history(cmdl);
	}
	else if (ret == CTRL_L)
	{
		CLEAR_SCREEN;
		MOVE_HOME;
		if (print_prompt())
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

void	insert_input(int ret, t_cmdline *cmdl)
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
	reset_cmd_line(&cmdl);
	while (true)
	{
		ret = 0;
		read_ret = read(STDIN_FILENO, &ret, 4);
		if (read_ret == -1)
			return (NULL);
		if (ft_isprint(ret))
			insert_input(ret, &cmdl);
		else if ((ret & 0xff) == ESCAPE)
			csi_handler(ret, &cmdl);
		else if ((ret == '\n' || ret == '\r'))
		{
			cmdl.buff[cmdl.size] = 0;
			flush_history(&cmdl);
			ft_printf("\n");
			return (ft_strdup(cmdl.buff));
		}
		else if (ft_isascii(ret))
			check_control(ret, &cmdl);
	}
}

int	do_stuff(void)
{
	char			*line;
	struct termios	term_backup;

	ft_bzero(&term_backup, sizeof(term_backup));
	while (true)
	{	
		if (setup_terminal(&term_backup))
			return (ft_perror("setup_terminal"));
		line = read_line(NULL);
		reset_terminal(&term_backup);
		if (!line)
			return (ft_perror("read_line"));
		parse_execute(line);
		free(line);
	}
}
