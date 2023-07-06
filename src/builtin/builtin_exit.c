/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:10:14 by dlu               #+#    #+#             */
/*   Updated: 2023/07/06 08:46:10 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_exit(t_cmd *cmd)
{
	if (cmd->args[1])
		gtfo(g_shell.cmdl, ft_atoi(cmd->args[1]));
	else
		gtfo(g_shell.cmdl, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
