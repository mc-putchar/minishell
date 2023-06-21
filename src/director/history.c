/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:39:23 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/21 02:18:20 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_down_history(t_cmdline *cmdl)
{
	t_list	*tmp;
	char	*line;

	if (!g_shell.hist)
		return ;
	if (g_shell.hist_i-- == 1)
	{
		if (cmdl->hist)
		{
			cmdl->size = ft_strlen(cmdl->hist);
			(void)ft_memcpy(cmdl->buff, cmdl->hist, cmdl->size);
			free(cmdl->hist);
			cmdl->hist = NULL;
		}
		else
			cmdl->size = 0;
		CLEAR_LINE;
		(void)ft_printf("%s%s", cmdl->prompt, cmdl->buff);
		cmdl->i = cmdl->size;
		return ;
	}
	tmp = ft_lstget_atindex(g_shell.hist, g_shell.hist_i);
	if (!tmp)
		return ;
	line = tmp->content;
	cmdl->buff[cmdl->size] = 0;
	(void)ft_memcpy(cmdl->buff, line, ft_strlen(line));
	CLEAR_LINE;
	(void)ft_printf("%s%s", cmdl->prompt, line);
	cmdl->i = cmdl->size;
}

void	ctrl_up_history(t_cmdline *cmdl)
{
	t_list	*tmp;

	if (!g_shell.hist)
		return ;
	if (ft_lstsize(g_shell.hist) > g_shell.hist_i)
	{
		tmp = ft_lstget_atindex(g_shell.hist, g_shell.hist_i);
		if (!tmp)
			return ;
		if (g_shell.hist_i++ == 0)
		{
			cmdl->hist = ft_strdup(cmdl->buff);
			if (!cmdl->hist)
				return ;
		}
		CLEAR_LINE;
		(void)ft_printf("%s%s", cmdl->prompt, tmp->content);
		cmdl->size = ft_strlen(tmp->content);
		(void)ft_memcpy(cmdl->buff, tmp->content, cmdl->size);
		cmdl->i = cmdl->size;
	}
}
		
int	read_history(int fd)
{
	t_list	*hist;
	t_list	*tmp;
	char	*line;

	hist = NULL;
	line = get_delim(fd, '\n');
	while (line)
	{
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
	char	*line;
	int		fd;

	if (!g_shell.hist)
		return (EXIT_SUCCESS);
	fd = open(HIST_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (ft_dprintf(STDERR_FILENO, "Error: open: %s\n", HIST_FILE));
	rev = g_shell.hist;
	tmp = g_shell.hist->next;
	while (tmp)
	{
		ft_lstadd_front(&rev, tmp);
		tmp = tmp->next;
	}
	while (rev)
	{
		line = rev->content;
		(void)ft_dprintf(fd, "%s\n", line);
		rev = rev->next;
	}
	close(fd);
	return (EXIT_SUCCESS);
}

int	flush_history(t_cmdline *cmdl)
{
	t_list	*tmp;
	char	*line;

	if (!cmdl->buff[0])
		return (EXIT_SUCCESS);
	line = ft_strjoin(cmdl->buff, "\n");
	if (!line)
		return (ft_dprintf(STDERR_FILENO, "Error: ft_strjoin\n"));
	tmp = ft_lstnew(line);
	if (!tmp)
		return (ft_dprintf(STDERR_FILENO, "Error: ft_lstnew\n"));
	if (!g_shell.hist)
		g_shell.hist = tmp;
	else
		ft_lstadd_front(&g_shell.hist, tmp);
	return (EXIT_SUCCESS);
}

int	init_history(void)
{
	char	*home;
	char	*path;
	int		fd;

	g_shell.hist = NULL;
	g_shell.hist_i = 0;
	home = getenv("HOME");
	if (!home)
		return (ft_dprintf(STDERR_FILENO, "Error: getenv\n"));
	path = ft_strjoin(home, HIST_FILE);
	if (!path)
		return (ft_dprintf(STDERR_FILENO, "Error: ft_strjoin\n"));
	if (access(path, F_OK) == -1)
	{
		free(path);
		return (EXIT_SUCCESS);
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (ft_dprintf(STDERR_FILENO, "Error: open: %s\n", path));
	free(path);
	if (read_history(fd))
		return (ft_dprintf(STDERR_FILENO, "Error: read_history\n"));
	close(fd);
	return (EXIT_SUCCESS);
}
