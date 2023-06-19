/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 22:05:50 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/19 17:10:06 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_cmd *cmd, char * const envp[])
{
	(void)cmd;
	(void)envp;
	return (EXIT_SUCCESS);
}

int	ft_unset(t_cmd *cmd, char * const envp[])
{
	(void)cmd;
	(void)envp;
	return (EXIT_SUCCESS);
}

int	ft_cd(t_cmd *cmd, char * const envp[])
{
	(void)cmd;
	(void)envp;
	return (EXIT_SUCCESS);
}

int	builtin(t_cmd *cmd, char * const envp[])
{
	(void)cmd;
	(void)envp;
	// if (!ft_strcmp(cmd->cmd->args[0], "echo"))
	// 	return (ft_echo(cmd->cmd->args));
	// else if (!ft_strcmp(cmd->cmd->args[0], "cd"))
	// 	return (ft_cd(cmd->cmd->args));
	// else if (!ft_strcmp(cmd->cmd->args[0], "pwd"))
	// 	return (ft_pwd());
	// else if (!ft_strcmp(cmd->cmd->args[0], "export"))
	// 	return (ft_export(cmd->cmd->args));
	// else if (!ft_strcmp(cmd->cmd->args[0], "unset"))
	// 	return (ft_unset(cmd->cmd->args));
	// else if (!ft_strcmp(cmd->cmd->args[0], "env"))
	// 	return (ft_env(envp));
	// else if (!ft_strcmp(cmd->cmd->args[0], "exit"))
	// 	return (exit_shell(cmd->cmd->args));
	return (EXIT_FAILURE);
}
