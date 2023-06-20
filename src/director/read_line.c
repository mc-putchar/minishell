/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 17:36:35 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/20 17:02:59 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete(char *buff, int *i, int *size)
{
	CLEAR_REST;
	ft_memcpy(&buff[*i], &buff[*i + 1], *size - *i);
	buff[*size] = 0;
	write(1, &buff[*i], *size - *i);
	(*size)--;
	if (*size > *i)
		MOVE_LEFT(*size - *i);
}

void	csi_handler(int ret, char *buff, int *i, int *size)
{
	if (ret == ARROW_UP)
		ft_printf("UP");
	else if (ret == ARROW_DOWN)
		ft_printf("DOWN");
	else if (ret == ARROW_RIGHT && *i < *size && ++(*i))
		MOVE_RIGHT(1);
	else if (ret == ARROW_LEFT && *i > 0 && (*i)--)
		MOVE_LEFT(1);
	else if (ret == DELETE && *i < *size)
		delete(buff, i, size);
}

void	check_control(int ret, char *prompt, char *buff, int *i)
{
	if (ret == CTRL_D)
		gtfo(prompt);
	else if (ret == CTRL_C)
	{
		ft_printf("^C");
		reset_cmd_line(prompt, buff, i);
	}
	else if (ret == CTRL_L)
	{
		CLEAR_SCREEN;
		MOVE_HOME;
		ft_printf("%s%s", prompt, buff);
		MOVE_HOME;
		MOVE_RIGHT(ft_strlen(prompt) + *i);
	}
}

void	insert_input(int ret, char *buff, int *i, int *size)
{
	if (*i == *size)
	{
		buff[(*i)++] = ret;
		write(1, &buff[*i - 1], 1);
		(*size)++;
	}
	else
	{
		(*size)++;
		ft_memmove(&buff[*i + 1], &buff[*i], *size - *i);
		buff[(*i)++] = ret;
		write(1, &buff[*i - 1], *size + 1 - *i);
		MOVE_LEFT(*size - *i + 1);
	}
}

char	*read_line(char *prompt)
{
	char	buff[BUFSIZ];
	int		i;
	int		size;
	int		ret;
	ssize_t	read_ret;

	i = 0;
	size = 0;
	reset_cmd_line(prompt, buff, &i);
	while (1)
	{
		read_ret = read(STDIN_FILENO, &ret, 4);
		if (read_ret == -1)
			return (NULL);
		if (ft_isprint(ret))
			insert_input(ret, buff, &i, &size);
		else if ((ret & 0xff) == ESCAPE)
			csi_handler(ret, &buff[0], &i, &size);
		else if ((ret == '\n' || ret == '\r') && ft_printf("\n"))
			return (ft_strdup(ft_memcpy(&buff[i], "\0", 2)));
		else if (ft_isascii(ret))
			check_control(ret, prompt, buff, &i);
		ret = 0;
	}
}

int	do_stuff(void)
{
	char			*line;
	char			*prompt;
	struct termios	term_backup;

	ft_bzero(&term_backup, sizeof(term_backup));
	prompt = build_prompt();
	if (!prompt)
		return (ft_dprintf(STDERR_FILENO, "Error: build_prompt\n"));
	while (1)
	{	
		if (setup_terminal(&term_backup))
			return (ft_dprintf(STDERR_FILENO, "Error: setup_terminal\n"));
		line = read_line(prompt);
		reset_terminal(&term_backup);
		if (!line)
			return (ft_dprintf(STDERR_FILENO, "Error: read_line\n"));
		if (!ft_strncmp(line, "exit\n", 5))
			gtfo(prompt);
		// TODO: replace this printing with parsing and executing
		if (ft_strchr(line, '\n') && ft_strlen(line) > 1)
			ft_dprintf(STDOUT_FILENO, "%s", line);
		free(line);
	}
}

