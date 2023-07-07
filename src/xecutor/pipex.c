/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 13:34:17 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/07 07:52:25 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	wait_for_child(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_SUCCESS);
}

static int	pipeline_len(t_cmd *cmd)
{
	int		len;
	t_cmd	*node;

	len = 0;
	node = cmd;
	while (node)
	{
		len++;
		node = node->pipe;
	}
	return (len);
}

static int	close_pipes(int fd[2][2])
{
	return (close(fd[0][0]) || close(fd[0][1]) || \
		close(fd[1][0]) || close(fd[1][1]));
}

static int	supermario(t_cmd *cmd, int i, int len, int fd[2][2])
{
	char	**args;

	if (i)
		if (dup2(fd[i & 1][0], STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
	if (i < len - 1)
		if (dup2(fd[(i + 1) & 1][1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
	if (!redir_setup(cmd))
		exit(EXIT_FAILURE);
	if (!cmd->args[0])
		exit(EXIT_SUCCESS);
	if (close_pipes(fd))
		exit(EXIT_FAILURE);
	args = cmd_expansion(cmd->args);
	args[0] = cmd_path(args[0]);
	if (!args[0] && invalid_command(cmd))
		exit(EXIT_FAILURE);
	if (execve(args[0], args, g_shell.envp) == -1)
		exit(EXIT_FAILURE);
	return (EXIT_FAILURE);
}

int	pipex(t_cmd *cmd)
{
	const int	pipelen = pipeline_len(cmd);
	int			fd[2][2];
	pid_t		*pids;
	int			i;

	if (pipe(fd[0]) == -1 || pipe(fd[1]) == -1)
		return (EXIT_FAILURE);
	pids = malloc(sizeof(pid_t) * pipelen);
	if (!pids)
		return (EXIT_FAILURE);
	i = -1;
	while (++i < pipelen)
	{
		ft_wait(100000);
		pids[i] = fork();
		if (pids[i] < 0 || (!pids[i] && supermario(cmd, i, pipelen, fd)))
			return (free(pids), EXIT_FAILURE);
		cmd = cmd->pipe;
	}
	(void)close_pipes(fd);
	i = -1;
	while (++i < pipelen)
		pids[i] = wait_for_child(pids[i]);
	return (free(pids), EXIT_SUCCESS);
}
