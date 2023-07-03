/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xecutor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 01:36:26 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/03 17:38:24 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char **environ; // change to the global struct later on
					   // or edit __environ directly

static int	simple(t_cmd *cmd)
{
	pid_t	pid;
	int		status;
	char	**args;

	pid = fork();
	if (pid < 0)
		return (EXIT_FAILURE);
	if (!pid)
	{
		args = cmd_expansion(cmd->args);
		args[0] = cmd_path(cmd);
		if (execve(args[0], args, environ) == -1)
			return (EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_SUCCESS);
}

/*
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
*/

/* Evalute left node first, only evalute right node if succeeds. */
static int	and(t_cmd *cmd)
{
	int	status;

	if (executor(cmd->left) == EXIT_SUCCESS)
		status = executor(cmd->right);
	else
		status = EXIT_FAILURE;
	return (status);
}

/* Evaluate left node first, only evalute right node if fails. */
static int	or(t_cmd *cmd)
{
	int	status;

	if (executor(cmd->left) == EXIT_SUCCESS)
		status = EXIT_SUCCESS;
	else
		status = executor(cmd->right);
	return (status);
}

/* Couldn't find the command, print error message. */
static int	invalid_command(t_cmd *cmd)
{
	ft_dprintf(STDERR_FILENO, "minishell: %s: command not found\n",
		cmd->args[0]);
	return (EXIT_FAILURE);
}

/* Execute a command node, possible types are AND, OR, or COMMAND. */
int	executor(t_cmd *cmd)
{
	if (cmd->type == AND)
		return (and(cmd));
	else if (cmd->type == OR)
		return (or(cmd));
	else if (is_builtin(cmd))
		return (execute_builtin(cmd));
	else if (cmd_validator(cmd))
		return (simple(cmd));
	else
		return (invalid_command(cmd));
	return (EXIT_FAILURE);
}
