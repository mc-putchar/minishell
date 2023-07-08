/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 13:34:17 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/08 17:33:32 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	wait_for_children(pid_t *pids, int len)
{
	int	i;
	int	status;

	i = -1;
	while (++i < len)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
	}
	return (status);
}

static int	pipeline_len(t_cmd *cmd)
{
	int		len;

	len = 0;
	while (cmd && ++len)
		cmd = cmd->pipe;
	return (len);
}

static int	supermario(t_cmd *cmd, int i, int len, int fd[2][2])
{
	char	**args;
	char	*path;

	if (i && (dup2(fd[(i - 1) & 1][0], STDIN_FILENO) == -1 || \
		close(fd[(i - 1) & 1][1]) || close(fd[(i - 1) & 1][0])))
		exit(EXIT_FAILURE);
	if (i < len - 1 && (dup2(fd[i & 1][1], STDOUT_FILENO) == -1 || \
		close(fd[i & 1][0]) || close(fd[i & 1][1])))
		exit(EXIT_FAILURE);
	if (is_builtin(cmd))
		exit(execute_builtin(cmd));
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
	return (EXIT_FAILURE);
}

static int	luigi(int i, int len, int fd[2][2])
{
	if (i == len - 1)
	{
		if (i > 1 && (close(fd[i & 1][0]) || close(fd[i & 1][1])))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (i & 1)
	{
		if (i > 1 && (close(fd[1][0]) || close(fd[1][1])))
			return (EXIT_FAILURE);
		if (pipe(fd[1]))
			return (EXIT_FAILURE);
	}
	else
	{
		if (i && (close(fd[0][0]) || close(fd[0][1])))
			return (EXIT_FAILURE);
		if (pipe(fd[0]))
			return (EXIT_FAILURE);
	}
	ft_wait(100000);
	return (EXIT_SUCCESS);
}

int	pipex(t_cmd *cmd)
{
	const int	pipelen = pipeline_len(cmd);
	int			fd[2][2];
	pid_t		*pids;
	int			i;

	pids = malloc(sizeof(pid_t) * pipelen);
	if (!pids)
		return (EXIT_FAILURE);
	i = -1;
	while (++i < pipelen)
	{
		if (luigi(i, pipelen, fd))
			return (free(pids), ft_dprintf(STDERR_FILENO, "%s %s: %s", MISH, \
				"pipex", strerror(errno)), EXIT_FAILURE);
		pids[i] = fork();
		if (pids[i] < 0 || (!pids[i] && supermario(cmd, i, pipelen, fd)))
			return (free(pids), ft_dprintf(STDERR_FILENO, "%s %s: %s", MISH, \
				"pipex", strerror(errno)), EXIT_FAILURE);
		cmd = cmd->pipe;
	}
	if (close(fd[i & 1][0]) || close(fd[i & 1][1]))
		ft_dprintf(STDERR_FILENO, "%s %s: %s", MISH, "pipex", strerror(errno));
	signal_suspend();
	i = wait_for_children(pids, pipelen);
	return (signal_restore(), free(pids), i);
}
