/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 22:05:50 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/17 12:18:42 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Attempt to execute a builtin command. */
int	execute_builtin(t_cmd *cmd)
{
	if (ft_strncmp(cmd->args[0], "echo", 4) == 0)
		return (builtin_echo(cmd));
	else if (ft_strncmp(cmd->args[0], "cd", 2) == 0)
	{
		if (builtin_cd(cmd) < 0)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	else if (ft_strncmp(cmd->args[0], "pwd", 3) == 0)
		return (builtin_pwd(cmd));
	else if (ft_strncmp(cmd->args[0], "export", 6) == 0)
		return (builtin_export(cmd));
	else if (ft_strncmp(cmd->args[0], "unset", 5) == 0)
		return (builtin_unset(cmd));
	else if (ft_strncmp(cmd->args[0], "env", 3) == 0)
		return (builtin_env(cmd));
	else if (ft_strncmp(cmd->args[0], "exit", 4) == 0)
		return (builtin_exit(cmd));
	else if (ft_strncmp(cmd->args[0], "help", 4) == 0)
		return (builtin_help(cmd));
	else
		return (EXIT_FAILURE);
}

/* Check if a command is a builtin. */
bool	is_builtin(t_cmd *cmd)
{
	const char	*c = cmd->args[0];

	if (!c)
		return (false);
	else if (ft_strlen(c) == 4 && ft_strncmp(c, "echo", 4) == 0)
		return (true);
	else if (ft_strlen(c) == 2 && ft_strncmp(c, "cd", 2) == 0)
		return (true);
	else if (ft_strlen(c) == 3 && ft_strncmp(c, "pwd", 3) == 0)
		return (true);
	else if (ft_strlen(c) == 6 && ft_strncmp(c, "export", 6) == 0)
		return (true);
	else if (ft_strlen(c) == 5 && ft_strncmp(c, "unset", 5) == 0)
		return (true);
	else if (ft_strlen(c) == 3 && ft_strncmp(c, "env", 3) == 0)
		return (true);
	else if (ft_strlen(c) == 4 && ft_strncmp(c, "exit", 4) == 0)
		return (true);
	else if (ft_strlen(c) == 4 && ft_strncmp(c, "help", 4) == 0)
		return (true);
	else
		return (false);
}
