/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_script.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 11:34:09 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/15 14:31:04 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_comment(char *line)
{
	int		i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		++i;
	if (line[i] == '#')
		return (1);
	return (0);
}

int	run_script(int fd)
{
	char	*line;

	g_shell.status = 0;
	line = get_delim(fd, '\n');
	while (line)
	{
		if (is_comment(line))
		{
			free(line);
			line = get_delim(fd, '\n');
			continue ;
		}
		line[ft_strlen(line) - 1] = '\0';
		parse_execute(line);
		line = get_delim(fd, '\n');
	}
	return (g_shell.status);
}

int	open_script(char *file)
{
	int		fd;
	int		status;

	if (!file)
		return (EXIT_FAILURE);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_dprintf(STDERR_FILENO, "%s: %s: %s\r\n", MISH, file, \
			strerror(errno)), EXIT_FAILURE);
	status = run_script(fd);
	close(fd);
	return (status);
}
