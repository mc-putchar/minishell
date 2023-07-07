/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:02:34 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/07 16:46:35 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			return (ft_strarrfree(paths), free(subpath), NULL);
		if (!access(path, X_OK))
			return (ft_strarrfree(paths), free(subpath), path);
		free(subpath);
		free(path);
	}
	return (ft_strarrfree(paths), NULL);
}

/* Get actual command path, validated first so it should never fail. */
char	*cmd_path(char *cmd)
{
	char	*path;

	if (!cmd)
		return (NULL);
	path = find_path(cmd);
	if (path)
		return (path);
	if (cmd[0] == '.' || cmd[0] == '/')
	{
		if (!access(cmd, X_OK))
			return (cmd);
	}
	if (ft_strchr(cmd, '/') && !access(cmd, X_OK))
		return (cmd);
	return (NULL);
}
