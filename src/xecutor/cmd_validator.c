/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:02:34 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/20 18:19:24 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

static char	*find_path(char *cmdname)
{
	char	*path;
	char	**paths;

	paths = ft_split(getenv("PATH"), ':');
	if (!paths)
		return (NULL);
	while (*paths)
	{
		path = ft_strjoin(*paths, cmdname);
		if (!path)
			return (free_paths(paths), NULL);
		if (!access(path, X_OK))
			return (free_paths(paths), path);
		free(path);
		paths++;
	}
	free_paths(paths);
	return (NULL);
}

char	*cmd_validator(t_cmd *cmd)
{
	char	*path;

	path = find_path(cmd->args[0]);
	if (path)
		return (path);
	if (cmd->args[0][0] == '.' || cmd->args[0][0] == '/')
	{
		if (!access(cmd->args[0], X_OK))
			return (cmd->args[0]);
	}
	if (ft_strchr(cmd->args[0], '/') && !access(cmd->args[0], X_OK))
		return (cmd->args[0]);
	ft_dprintf(STDERR_FILENO, "minishell: %s: command not found\n", \
		cmd->args[0]);
	return (NULL);
}
