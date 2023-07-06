/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:05:42 by dlu               #+#    #+#             */
/*   Updated: 2023/07/06 09:16:08 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Change current directory to the first argument. */
int	builtin_cd(t_cmd *cmd)
{
	char	buffer[BUFFER_SIZE];
	char	*temp;
	int		status;

	temp = arg_expansion(cmd->args[1]);
	status = chdir(temp);
	if (status < 0)
		ft_dprintf(STDERR_FILENO, "minishell: cd: %s: %s\n", temp,
			strerror(errno));
	else
	{
		getcwd(buffer, BUFFER_SIZE);
		free(temp);
		temp = ft_strjoin("OLDPWD=", getenv("PWD"));
		replace_env("OLDPWD", temp);
		temp = ft_strjoin("PWD=", buffer);
		replace_env("PWD", temp);
	}
	return (free(temp), status);
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
