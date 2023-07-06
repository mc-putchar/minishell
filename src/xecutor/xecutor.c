/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xecutor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 01:36:26 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/06 16:36:43 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (!redir_setup(cmd))
			exit(EXIT_FAILURE);
		if (!cmd->args[0])
			exit(EXIT_SUCCESS);
		args = cmd_expansion(cmd->args);
		args[0] = cmd_path(cmd);
		if (!args[0] && invalid_command(cmd))
			exit(EXIT_FAILURE);
		if (execve(args[0], args, g_shell.envp) == -1)
			return (EXIT_FAILURE);
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
int	invalid_command(t_cmd *cmd)
{
	ft_wait(100000);
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
	else if (cmd->pipe)
		return (pipex(cmd));
	else if (is_builtin(cmd))
		return (execute_builtin(cmd));
	else if (cmd_validator(cmd))
		return (simple(cmd));
	else
		return (invalid_command(cmd));
}
