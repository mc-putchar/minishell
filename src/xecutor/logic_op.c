/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:31:03 by dlu               #+#    #+#             */
/*   Updated: 2023/07/07 16:31:20 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Evalute left node first, only evalute right node if succeeds. */
int	cmd_and(t_cmd *cmd)
{
	int	status;

	status = executor(cmd->left);
	if (status == EXIT_SUCCESS)
		status = executor(cmd->right);
	return (status);
}

/* Evaluate left node first, only evalute right node if fails. */
int	cmd_or(t_cmd *cmd)
{
	int	status;

	status = executor(cmd->left);
	if (status != EXIT_SUCCESS)
		status = executor(cmd->right);
	return (status);
}
