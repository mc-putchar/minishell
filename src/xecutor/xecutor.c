/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xecutor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 01:36:26 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/07 13:24:31 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	simple(t_cmd *cmd)
{
	pid_t	pid;
	int		status;
	char	**args;
	char	*path;

	pid = fork();
	if (pid < 0)
		return (EXIT_FAILURE);
	if (!pid)
	{
		if (!redir_setup(cmd))
			exit(EXIT_FAILURE);
		if (!cmd->args[0])
			exit(EXIT_SUCCESS);
		args = cmd_expansion(cmd->args);
		path = cmd_path(args[0]);
		if (!path && invalid_command(cmd))
			exit(EXIT_FAILURE);
		if (execve(path, args, g_shell.envp) == -1)
			exit(EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_SUCCESS);
}

/* Evalute left node first, only evalute right node if succeeds. */
static int	and(t_cmd *cmd)
{
	int	status;

	status = executor(cmd->left);
	if (status == EXIT_SUCCESS)
		status = executor(cmd->right);
	return (status);
}

/* Evaluate left node first, only evalute right node if fails. */
static int	or(t_cmd *cmd)
{
	int	status;

	status = executor(cmd->left);
	if (status != EXIT_SUCCESS)
		status = executor(cmd->right);
	return (status);
}

/* Couldn't find the command, print error message. */
int	invalid_command(t_cmd *cmd)
{
	ft_dprintf(STDERR_FILENO, MISH": %s: command not found\n",
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
	else if (cmd->pipe)
		return (pipex(cmd));
	else if (is_builtin(cmd))
		return (execute_builtin(cmd));
	else
		return (simple(cmd));
}
