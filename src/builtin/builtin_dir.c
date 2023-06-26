/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:05:42 by dlu               #+#    #+#             */
/*   Updated: 2023/06/26 18:55:55 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: have to handle expansion; i.e. export TEST=.. && cd $TEST
int	builtin_cd(t_cmd *cmd)
{
	int	status;

	status = chdir(cmd->args[1]);
	if (status < 0)
		ft_dprintf(STDERR_FILENO, "minishell: cd: %s: %s\n", cmd->args[1],
			strerror(errno));
	return (status);
}

// TODO: redirection
int	builtin_pwd(t_cmd *cmd)
{
	char	buffer[BUFFER_SIZE];

	(void) cmd;
	getcwd(buffer, BUFFER_SIZE);
	ft_printf("%s\n", buffer);
	return (EXIT_SUCCESS);
}
