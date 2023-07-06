/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:53:13 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/06 01:10:19 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// initialize from .mshrc and .msh_hist files
int	init_shell(void)
{
	// char	*home;
	// char	*path;
	// int		fd;

	// home = getenv("HOME");
	// if (!home)
	// 	return (ft_perror("getenv"));
	// path = ft_strjoin(home, RC_FILE);
	// if (!path)
	// 	return (ft_perror("ft_strjoin"));
	// if (access(path, F_OK))
	// 	return (EXIT_SUCCESS);
	// fd = open(path, O_RDONLY);
	// if (fd == -1)
	// 	return (ft_dprintf(STDERR_FILENO, "Error: open: %s\n", path));
	// 	// probably replace with system perror
	// free(path);
	// if (read_rc(fd))
	// 	return (ft_perror("read_rc"));
	// close(fd);
	(void)init_history();
	return (EXIT_SUCCESS);
}
