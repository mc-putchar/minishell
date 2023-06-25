/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xecutor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 01:36:26 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/25 17:06:52 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	simple(char **args, char * const envp[])
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (EXIT_FAILURE);
	if (!pid)
		if (execve(args[0], args, envp) == -1)
			return (EXIT_FAILURE);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_SUCCESS);
}

static int	pipex(t_cmd *cmd, char * const envp[])
{
	int		fd[2];
	pid_t	pid;
	pid_t	pid2;
	int		status;
	int		status2;

	if (pipe(fd) == -1)
		return (EXIT_FAILURE);
	pid = fork();
	if (pid < 0)
		return (EXIT_FAILURE);
	if (!pid)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			return (EXIT_FAILURE);
		if (execve(cmd->left->args[0], cmd->left->args, envp) == -1)
			return (EXIT_FAILURE);
	}
	close(fd[1]);
	pid2 = fork();
	if (pid2 < 0)
		return (EXIT_FAILURE);
	if (!pid2)
	{
		if (dup2(fd[0], STDIN_FILENO) == -1)
			return (EXIT_FAILURE);
		if (execve(cmd->right->args[0], cmd->right->args, envp) == -1)
			return (EXIT_FAILURE);
	}
	close(fd[0]);
	waitpid(pid, &status, 0);
	waitpid(pid2, &status2, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFEXITED(status2))
		return (WEXITSTATUS(status2));
	return (EXIT_SUCCESS);
}

static int	and(t_cmd *cmd, char * const envp[])
{
	int		status;

	if (executor(cmd->left, envp) == EXIT_SUCCESS)
		status = executor(cmd->right, envp);
	else
		status = EXIT_FAILURE;
	return (status);
}

static int	or(t_cmd *cmd, char * const envp[])
{
	int		status;

	if (executor(cmd->left, envp) == EXIT_SUCCESS)
		status = EXIT_SUCCESS;
	else
		status = executor(cmd->right, envp);
	return (status);
}

int	executor(t_cmd *cmd, char * const envp[])
{
	if (cmd->type == CMD)
		return (simple(cmd->args, envp));
	else if (cmd->type == PIPE)
		return (pipex(cmd, envp));
	else if (cmd->type == REDIR_IN)
		return (redir_in(cmd, envp));
	else if (cmd->type == REDIR_OUT)
		return (redir_out(cmd, envp));
	else if (cmd->type == REDIR_APPEND)
		return (redir_append(cmd, envp));
	else if (cmd->type == REDIR_HERE)
		return (redir_here(cmd, envp));
	else if (cmd->type == AND)
		return (and(cmd, envp));
	else if (cmd->type == OR)
		return (or(cmd, envp));
	else if (cmd->type == BUILTIN)
		return (builtin(cmd, envp));
	return (0);
}
