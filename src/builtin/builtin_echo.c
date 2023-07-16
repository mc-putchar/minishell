/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:48:57 by dlu               #+#    #+#             */
/*   Updated: 2023/07/16 17:56:57 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	backup_stdfds(int fd[2])
{
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
}

void	restore_stdfds(int fd[2])
{
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
}

/* Execute the builtin command, all arguments should be expanded. */
int	builtin_echo(t_cmd *cmd)
{
	const char	**av = (const char **) cmd_expansion(cmd->args);
	int			fd[2];
	bool		n_flag;
	int			i;

	n_flag = false;
	i = 0;
	backup_stdfds(fd);
	if (!redir_setup(cmd))
		return (ft_strarrfree((char **) av), EXIT_FAILURE);
	if (!cmd->execute)
		return (ft_strarrfree((char **) av), EXIT_FAILURE);
	while (av[++i])
	{
		if (i == 1 && ft_strlen(av[i]) == 2 && ft_strncmp("-n", av[1], 2) == 0)
			n_flag = true;
		else if (av[i + 1])
			ft_printf("%s ", av[i]);
		else if (!n_flag)
			ft_printf("%s\n", av[i]);
		else
			ft_printf("%s", av[i]);
	}
	restore_stdfds(fd);
	return (ft_strarrfree((char **) av), EXIT_SUCCESS);
}
