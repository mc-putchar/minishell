/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:02:34 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/04 17:23:39 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Free the path pointers. */
static void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

/* Search the executable path in order, NULL if not found. */
static char	*find_path(char *cmdname)
{
	char	*subpath;
	char	*path;
	char	**paths;
	int		i;

	paths = ft_split(getenv("PATH"), ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		subpath = ft_strjoin("/", cmdname);
		path = ft_strjoin(paths[i], subpath);
		if (!path)
			return (free_paths(paths), free(subpath), NULL);
		if (!access(path, X_OK))
			return (free_paths(paths), free(subpath), path);
		free(subpath);
		free(path);
	}
	return (free_paths(paths), NULL);
}

/* Get actual command path, validated first so it should never fail. */
char	*cmd_path(t_cmd *cmd)
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
	return (NULL);
}

/* Check if a command can be found. */
bool	cmd_validator(t_cmd *cmd)
{
	char	*path;

	path = find_path(cmd->args[0]);
	if (path)
		return (free(path), true);
	if (cmd->args[0][0] == '.' || cmd->args[0][0] == '/')
	{
		if (!access(cmd->args[0], X_OK))
			return (cmd->args[0]);
	}
	if (ft_strchr(cmd->args[0], '/') && !access(cmd->args[0], X_OK))
		return (cmd->args[0]);
	return (NULL);
}
