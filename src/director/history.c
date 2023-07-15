/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:39:23 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/15 16:45:42 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_history(int fd)
{
	t_list	*hist;
	t_list	*tmp;
	char	*line;

	hist = NULL;
	line = get_delim(fd, '\n');
	while (line)
	{
		line[ft_strlen(line) - 1] = 0;
		tmp = ft_lstnew(line);
		if (!tmp)
		{
			ft_lstclear(&hist, free);
			return (ft_dprintf(STDERR_FILENO, "Error: ft_lstnew\n"));
		}
		if (!hist)
			hist = tmp;
		else
			ft_lstadd_front(&hist, tmp);
		line = get_delim(fd, '\n');
	}
	g_shell.hist = hist;
	return (EXIT_SUCCESS);
}

int	write_history(void)
{
	t_list	*tmp;
	t_list	*rev;
	int		fd;
	char	*path;

	if (!g_shell.hist)
		return (EXIT_SUCCESS);
	path = ft_strjoin(g_shell.home, HIST_FILE);
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(path);
	if (fd < 0)
		return (EXIT_FAILURE);
	rev = g_shell.hist;
	tmp = g_shell.hist->next;
	while (tmp)
	{
		ft_lstadd_front(&rev, tmp);
		tmp = tmp->next;
	}
	while (rev)
	{
		(void)ft_dprintf(fd, "%s\n", rev->content);
		rev = rev->next;
	}
	return (EXIT_SUCCESS);
}

//TODO: save changed entries
int	flush_history(t_cmdline *cmdl)
{
	t_list	*tmp;
	char	*line;

	g_shell.hist_i = 0;
	if (cmdl->hist)
		free(cmdl->hist);
	if (!cmdl->buff[0])
		return (EXIT_SUCCESS);
	line = ft_strdup(cmdl->buff);
	if (!line)
		return (ft_dprintf(STDERR_FILENO, MISH": error: ft_strjoin\n"), \
			free(cmdl->buff), EXIT_FAILURE);
	tmp = ft_lstnew(line);
	if (!tmp)
		return (free(line), ft_dprintf(STDERR_FILENO, \
			MISH": error: ft_lstnew\n"), free(cmdl->buff), EXIT_FAILURE);
	if (!g_shell.hist)
		g_shell.hist = tmp;
	else
		ft_lstadd_front(&g_shell.hist, tmp);
	return (EXIT_SUCCESS);
}

static int	open_history(void)
{
	int		fd;
	char	*path;

	path = ft_strjoin(g_shell.home, HIST_FILE);
	if (g_shell.home && !path)
		return (ft_dprintf(STDERR_FILENO, MISH": error: ft_strjoin\n"), -1);
	if (!path || access(path, F_OK))
		return (free(path), -1);
	fd = open(path, O_RDONLY);
	free(path);
	if (fd == -1)
		return (ft_dprintf(STDERR_FILENO, MISH": %s: %s\n", \
			strerror(errno), HIST_FILE), -1);
	if (read_history(fd))
		return (ft_dprintf(STDERR_FILENO, MISH": error: read_history\n"), \
			close(fd), EXIT_FAILURE);
	close(fd);
	return (EXIT_SUCCESS);
}

int	init_history(void)
{
	int	fd;

	fd = open_history();
	if (fd > 0 && read_history(fd))
		return (close(fd), ft_dprintf(STDERR_FILENO, \
			MISH": error: read_history\n"), close(fd), EXIT_FAILURE);
	if (fd > 0)
		close(fd);
	g_shell.hist = NULL;
	g_shell.hist_i = 0;
	return (EXIT_SUCCESS);
}
