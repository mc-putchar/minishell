/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 21:33:59 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/27 13:52:59 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_in(t_cmd *cmd, char * const envp[])
{
	int		fd;
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (EXIT_FAILURE);
	if (!pid)
	{
		fd = open(cmd->right->args[1], O_RDONLY);
		if (fd == -1)
			return (EXIT_FAILURE);
		if (dup2(fd, STDIN_FILENO) == -1)
			return (EXIT_FAILURE);
		close(fd);
		if (execve(cmd->left->args[0], cmd->left->args, envp) == -1)
			return (EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_SUCCESS);
}

int	redir_out(t_cmd *cmd, char * const envp[])
{
	int		fd;
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (EXIT_FAILURE);
	if (!pid)
	{
		fd = open(cmd->right->args[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (EXIT_FAILURE);
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (EXIT_FAILURE);
		close(fd);
		if (execve(cmd->left->args[0], cmd->left->args, envp) == -1)
			return (EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_SUCCESS);
}

int	redir_append(t_cmd *cmd, char * const envp[])
{
	int		fd;
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (EXIT_FAILURE);
	if (!pid)
	{
		fd = open(cmd->right->args[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (EXIT_FAILURE);
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (EXIT_FAILURE);
		close(fd);
		if (execve(cmd->left->args[0], cmd->left->args, envp) == -1)
			return (EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_SUCCESS);
}

int	redir_here(t_cmd *cmd, char * const envp[])
{
	int		fd;
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (EXIT_FAILURE);
	if (!pid)
	{
		// TODO: HERE DOC
		(void)cmd;
		(void)envp;
		(void)fd;
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_SUCCESS);
}
