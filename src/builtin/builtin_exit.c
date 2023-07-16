/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:10:14 by dlu               #+#    #+#             */
/*   Updated: 2023/07/16 18:21:33 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ERR_ARG	"%s: exit: too many arguments\n"
#define ERR_NUM	"%s: exit: %s: numeric argument required\n"

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
	if (!isatty(STDIN_FILENO))
		return (EXIT_SUCCESS);
	if (ft_strarrlen(cmd->args) > 2)
	{
		ft_dprintf(STDERR_FILENO, ERR_ARG, MISH);
		return (EXIT_FAILURE);
	}
	if (cmd->args[1] && arg_isnum(cmd->args[1]))
		gtfo(g_shell.cmdl, ft_atoi(cmd->args[1]), "exit", false);
	else if (cmd->args[1])
	{
		ft_dprintf(STDERR_FILENO, ERR_NUM, MISH, cmd->args[1]);
		gtfo(g_shell.cmdl, 2, "exit", false);
	}
	else
		gtfo(g_shell.cmdl, EXIT_SUCCESS, "exit", false);
	return (EXIT_SUCCESS);
}
