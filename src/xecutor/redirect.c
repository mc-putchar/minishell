/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:14:35 by dlu               #+#    #+#             */
/*   Updated: 2023/07/16 17:29:29 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Open file based on the redirection type. */
static int	open_file(char *path, t_type type, int fd_default)
{
	char	*expand;
	int		fd;

	if (!path)
		return (fd_default);
	fd = 0;
	expand = arg_expansion(path);
	if (type == APPEND)
		fd = open(expand, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == REDIR_OUT)
		fd = open(expand, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == REDIR_IN)
		fd = open(expand, O_RDONLY);
	if (fd < 0)
		ft_dprintf(STDERR_FILENO, MISH": %s: %s\n", expand, strerror(errno));
	return (free(expand), fd);
}

/* Close the open file descriptors, return if any is still open. */
static bool	close_fd(t_cmd *cmd, int o_fd, int i_fd)
{
	if (o_fd < 0 && i_fd != STDIN_FILENO)
		return (close(i_fd), cmd->execute = false, false);
	if (i_fd < 0 && o_fd != STDOUT_FILENO)
		return (close(o_fd), cmd->execute = false, false);
	if (o_fd < 0 || i_fd < 0)
		return (cmd->execute = false, false);
	if (!cmd->args[0])
	{
		if (o_fd != STDOUT_FILENO)
			close(o_fd);
		if (i_fd != STDIN_FILENO)
			close(i_fd);
		return (false);
	}
	return (true);
}

/* Setup redirection for each command. */
bool	redir_setup(t_cmd *cmd)
{
	int	o_fd;
	int	i_fd;

	if (cmd->i_type == HERE_DOC)
	{
		if (dup2(cmd->here_doc, STDIN_FILENO) == -1)
			return (close(cmd->here_doc), false);
		return (close(cmd->here_doc), true);
	}
	o_fd = open_file(cmd->o_file, cmd->o_type, STDOUT_FILENO);
	i_fd = open_file(cmd->i_file, cmd->i_type, STDIN_FILENO);
	if (!close_fd(cmd, o_fd, i_fd))
		return (true);
	if (dup2(o_fd, STDOUT_FILENO) == -1)
		return (false);
	if (dup2(i_fd, STDIN_FILENO) == -1)
		return (false);
	return (true);
}
