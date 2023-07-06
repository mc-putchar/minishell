/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:14:35 by dlu               #+#    #+#             */
/*   Updated: 2023/07/06 07:34:37 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Open file based on the redirection type. */
int	open_file(char *path, t_type type)
{
	int	fd;

	fd = 0;
	if (type == APPEND)
		fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == REDIR_OUT)
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == REDIR_IN)
		fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", path, strerror(errno));
	return (fd);
}

/* Setup redirection for each command. */
bool	redir_setup(t_cmd *cmd)
{
	int	o_fd;
	int	i_fd;

	o_fd = STDOUT_FILENO;
	i_fd = STDIN_FILENO;
	if (cmd->o_file)
		o_fd = open_file(cmd->o_file, cmd->o_type);
	if (o_fd < 0)
		return (false);
	if (cmd->i_file)
		i_fd = open_file(cmd->i_file, cmd->i_type);
	if (i_fd < 0)
		return (close(o_fd), false);
	if (dup2(o_fd, STDOUT_FILENO) == -1)
		return (false);
	if (dup2(i_fd, STDIN_FILENO) == -1)
		return (false);
	return (true);
}
