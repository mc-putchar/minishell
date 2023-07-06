/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:10:14 by dlu               #+#    #+#             */
/*   Updated: 2023/07/06 15:19:01 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ERR_ARG	"minishell: exit: too many arguments\n"
#define ERR_NUM	"minishell: exit: %s: numeric argument required\n"

/* Check if argument is a numeric. */
static bool	arg_isnum(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (i == 0 && (arg[i] == '+' || arg[i] == '-'))
			continue ;
		if (!ft_isdigit(arg[i]))
			return (false);
	}
	return (true);
}

int	builtin_exit(t_cmd *cmd)
{
	if (ft_strarrlen(cmd->args) > 2)
	{
		ft_dprintf(STDERR_FILENO, ERR_ARG);
		return (EXIT_FAILURE);
	}
	if (cmd->args[1] && arg_isnum(cmd->args[1]))
		gtfo(g_shell.cmdl, ft_atoi(cmd->args[1]));
	else if (cmd->args[1])
	{
		ft_dprintf(STDERR_FILENO, ERR_NUM, cmd->args[1]);
		gtfo(g_shell.cmdl, 2);
	}
	else
		gtfo(g_shell.cmdl, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
