/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_environ.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:09:02 by dlu               #+#    #+#             */
/*   Updated: 2023/06/26 14:23:19 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_export(t_cmd *cmd)
{
	(void) cmd;
	return (EXIT_SUCCESS);
}

int	builtin_unset(t_cmd *cmd)
{
	(void) cmd;
	return (EXIT_SUCCESS);
}

int	builtin_env(t_cmd *cmd)
{
	(void) cmd;
	return (EXIT_SUCCESS);
}
