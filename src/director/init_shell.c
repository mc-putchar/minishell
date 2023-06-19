/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:53:13 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/19 17:14:10 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: implement history reading and writing to file
int	read_hist(int fd)
{
	char	buff[BUFSIZ];
	int		r;
	int		i;

	i = 0;
	r = read(fd, buff, BUFSIZ);
	return (EXIT_SUCCESS);
}

int	init_history(void)
{
	char	*home;
	char	*path;
	int		fd;

	home = getenv("HOME");
	if (!home)
		return (ft_dprintf(STDERR_FILENO, "Error: getenv\n"));
	path = ft_strjoin(home, HIST_FILE);
	if (!path)
		return (ft_dprintf(STDERR_FILENO, "Error: ft_strjoin\n"));
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (ft_dprintf(STDERR_FILENO, "Error: open: %s\n", path));
	free(path);
	if (read_hist(fd))
		return (ft_dprintf(STDERR_FILENO, "Error: read_history\n"));
	close(fd);
	return (EXIT_SUCCESS);
}

int	read_rc(int fd)
{
	char	*line;

	line = get_delim(fd, '\n');
	while (line)
	{
		if (line[0] == '#')
		{
			free(line);
			line = get_delim(fd, '\n');
			continue ;
		}
		// if (ft_strncmp(line, "export ", 7))
		// 	ft_export(line + 7);
		// else if (ft_strncmp(line, "unset ", 6))
		// 	ft_unset(line + 6);
		// else if (ft_strncmp(line, "cd ", 3) == 0)
		// 	ft_cd(line + 3);
		// else
		// 	ft_dprintf(STDERR_FILENO, "Error: unknown command: %s\n", line);
		free(line);
		line = get_delim(fd, '\n');
	}
	return (0);
}

// initialize from .minishellrc and .minishellhist files
int	init_shell(void)
{
	char	*home;
	char	*path;
	int		fd;

	home = getenv("HOME");
	if (!home)
		return (ft_dprintf(STDERR_FILENO, "Error: getenv\n"));
	path = ft_strjoin(home, RC_FILE);
	if (!path)
		return (ft_dprintf(STDERR_FILENO, "Error: ft_strjoin\n"));
	if (access(path, F_OK))
		return (EXIT_SUCCESS);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (ft_dprintf(STDERR_FILENO, "Error: open: %s\n", path));
	free(path);
	if (read_rc(fd))
		return (ft_dprintf(STDERR_FILENO, "Error: read_rc\n"));
	close(fd);
	(void)init_history();
	return (EXIT_SUCCESS);
}
