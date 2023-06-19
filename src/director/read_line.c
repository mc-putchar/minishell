/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 17:36:35 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/19 17:17:58 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// TODO: add history and line editing, fix left and right arrow behaviour
void	handle_esc(char *prompt, char *buff, int *i)
{
	if (!ft_strncmp(buff + *i, UP_ARROW, 3))
	{
		ft_bzero(buff, BUFSIZ);
		// *hist = (*hist)->prev;
		// ft_printf("%s", (*hist)->line);
		*i = 0;
	}
	else if (!ft_strncmp(buff + *i, DOWN_ARROW, 3))
	{
		ft_bzero(buff, BUFSIZ);
		// *hist = (*hist)->next;
		// ft_printf("%s", (*hist)->line);
		*i = 0;
	}
	else if (!ft_strncmp(buff + *i, LEFT_ARROW, 3) && *i > 0)
	{
		write(STDOUT_FILENO, "\b", 1);
		// ft_bzero(buff + *i, 1);
		*i -= 1;
	}
	else if (!ft_strncmp(buff + *i, RIGHT_ARROW, 3) && *i < BUFSIZ)
	{
		write(STDOUT_FILENO, RIGHT_ARROW, 3);
		++*i;
	}
	else if (!ft_strncmp(buff + *i, CTRL_DEL, 4))
	{
		ft_dprintf(STDOUT_FILENO, "\r\n%s :delete:", prompt);
		ft_bzero(buff, BUFSIZ);
		*i = 0;
	}
}

// TODO: refactor this function
char	*read_line(struct termios *term_backup, char *prompt)
{
	char	buff[BUFSIZ];
	char	*line;
	int		i;
	int		c;

	i = 0;
	ft_bzero(buff, BUFSIZ);
	reset_cmd_line(prompt, buff, &i);
	while (!ft_memchr(buff, '\r', i))
	{
		c = read(STDIN_FILENO, buff + i, BUFSIZ - i);
		if (c < 1)
			gtfo(term_backup, prompt);
		if (!ft_strncmp(&buff[i], CTRL_D, 1))
			gtfo(term_backup, prompt);
		if (!ft_strncmp(&buff[i], CTRL_C, 1))
		{
			write(STDOUT_FILENO, "^C", 2);
			reset_cmd_line(prompt, buff, &i);
		}
		else if (buff[i] == ESCAPE)
			handle_esc(prompt, buff, &i);
		else if (buff[i] == '\b')
		{
			write(STDOUT_FILENO, ":backspace:", 3);
			--i;
		}
		else
			i += write(STDOUT_FILENO, buff + i, c);
	}
	line = ft_substr(buff, 0, i);
	return (line);
}

int	do_stuff(struct termios *term_backup)
{
	char	*line;
	char	*prompt;

	prompt = build_prompt();
	if (!prompt)
		return (ft_dprintf(STDERR_FILENO, "Error: build_prompt\n"));
	line = read_line(term_backup, prompt);
	while (1)
	{
		//if (line[0])
		//	lexer(line);
		free(line);
		line = read_line(term_backup, prompt);
	}
	free(line);
	return (EXIT_SUCCESS);
}

