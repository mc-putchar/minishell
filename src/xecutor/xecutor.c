/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xecutor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 01:36:26 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/17 09:22:06 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Child process of the command. */
static void	cmd_exec(t_cmd *cmd)
{
	char	**args;
	char	*path;

	if (!redir_setup(cmd))
		gtfo(g_shell.cmdl, EXIT_FAILURE, NULL, true);
	if (!cmd->execute)
		gtfo(g_shell.cmdl, EXIT_FAILURE, NULL, true);
	if (!cmd->args[0])
		gtfo(g_shell.cmdl, EXIT_SUCCESS, NULL, true);
	args = cmd_expansion(cmd->args);
	path = cmd_path(args[0]);
	if (!path && invalid_command(cmd))
	{
		ft_strarrfree(args);
		gtfo(g_shell.cmdl, EXIT_CMD, NULL, true);
	}
	if (execve(path, args, g_shell.envp) == -1)
	{
		ft_strarrfree(args);
		gtfo(g_shell.cmdl, EXIT_FAILURE, NULL, true);
	}
}

/* Execute one simple command. */
static int	simple(t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (EXIT_FAILURE);
	if (!pid)
		cmd_exec(cmd);
	signal_suspend();
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (signal_restore(), EXIT_SUCCESS);
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
		return (cmd_and(cmd));
	else if (cmd->type == OR)
		return (cmd_or(cmd));
	else if (cmd->pipe)
		return (pipex(cmd));
	else if (is_builtin(cmd))
		return (execute_builtin(cmd));
	else
		return (simple(cmd));
}
