/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:05:42 by dlu               #+#    #+#             */
/*   Updated: 2023/07/07 14:51:52 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Change current directory to the first argument. */
int	builtin_cd(t_cmd *cmd)
{
	char	buffer[BUFFER_SIZE];
	char	*temp;
	int		status;

	if (!cmd->args[1] || !ft_strncmp(cmd->args[1], "~", 1))
		temp = ft_strdup(g_shell.home);
	else if (!ft_strncmp(cmd->args[1], "-", 1) && ft_getenv("OLDPWD"))
		temp = ft_strdup(ft_getenv("OLDPWD"));
	else
		temp = arg_expansion(cmd->args[1]);
	(void)getcwd(buffer, BUFFER_SIZE);
	status = chdir(temp);
	if (status < 0)
		ft_dprintf(STDERR_FILENO, MISH": cd: %s: %s\n", temp, strerror(errno));
	else
	{
		free(temp);
		temp = ft_strjoin("OLDPWD=", buffer);
		replace_env("OLDPWD", temp);
		free(temp);
		(void)getcwd(buffer, BUFFER_SIZE);
		temp = ft_strjoin("PWD=", buffer);
		replace_env("PWD", temp);
	}
	return (free(temp), status);
}

int	builtin_pwd(t_cmd *cmd)
{
	char	buffer[BUFFER_SIZE];
	int		fd[2];

	backup_stdfds(fd);
	if (!redir_setup(cmd))
		return (EXIT_FAILURE);
	(void) cmd;
	getcwd(buffer, BUFFER_SIZE);
	ft_printf("%s\r\n", buffer);
	restore_stdfds(fd);
	return (EXIT_SUCCESS);
}
