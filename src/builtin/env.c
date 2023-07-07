/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 18:29:22 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/07 15:04:59 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Return the value of an environment variable.
** @param name Name of the variable.
** @return Value of the variable, or NULL if not found.
*/
char	*ft_getenv(char *name)
{
	int		i;
	int		len;
	char	*var;

	i = 0;
	len = ft_strlen(name);
	while (g_shell.envp[i])
	{
		var = g_shell.envp[i];
		if (!ft_strncmp(var, name, len) && var[len] == '=' && var[len + 1])
			return (var + len + 1);
		++i;
	}
	return (NULL);
}

/*
** Add or modify an environment variable.
** Passed string is stored as reference, not copied.
** @param str String in the form "NAME=VALUE".
** @return 0 on success, 1 on error.
*/
// int	ft_putenv(char *str)
// {
// 	int		i;
// 	int		off;
// 	char	**tmp;

// 	i = -1;
// 	if (!ft_strchr(str, '='))
// 		return (EXIT_FAILURE);
// 	off = ft_strchr(str, '=') - str;
// 	while (g_shell.envp[++i])
// 	{
// 		if (!ft_strncmp(g_shell.envp[i], str, off) && \
// 			g_shell.envp[i][off] == '=')
// 		{
// 			free(g_shell.envp[i]);
// 			g_shell.envp[i] = str;
// 			return (EXIT_SUCCESS);
// 		}
// 	}
// 	tmp = ft_memgrow(g_shell.envp, sizeof(char *) * (i + 1), \
// 		sizeof(char *) * (i + 2));
// 	if (!tmp)
// 		return (EXIT_FAILURE);
// 	g_shell.envp = tmp;
// 	g_shell.envp[i] = str;
// 	g_shell.envp[i + 1] = NULL;
// 	return (EXIT_SUCCESS);
// }

/*
** Add or modify an environment variable.
** If name exists and overwrite is non-zero, the value is modified.
** Strings pointed by name and value are duplicated.
** @param name Name of the variable.
** @param value Value of the variable.
** @param overwrite Overwrite flag.
** @return 0 on success, 1 on error.
*/
int	ft_setenv(char *name, char *value, int overwrite)
{
	int			i;
	int const	len = ft_strlen(name);
	char		*var;
	char		*str;

	i = -1;
	while (g_shell.envp[++i])
	{
		var = g_shell.envp[i];
		if (!ft_strncmp(var, name, len) && var[len] == '=')
		{
			if (!overwrite)
				return (EXIT_SUCCESS);
			break ;
		}
	}
	str = NULL;
	var = ft_strjoin(name, "=");
	if (var)
		str = ft_strjoin(var, value);
	free(var);
	if (!str)
		return (EXIT_FAILURE);
	free(g_shell.envp[i]);
	g_shell.envp[i] = str;
	return (EXIT_SUCCESS);
}

// int	init_env(char **envp)
// {
// 	int		i;
// 	char	*var;

// 	i = 0;
// 	while (envp[i])
// 		++i;
// 	g_shell.envp = malloc(sizeof(char *) * (i + 1));
// 	if (!g_shell.envp)
// 		return (EXIT_FAILURE);
// 	g_shell.envp[i] = NULL;
// 	while (i--)
// 	{
// 		var = ft_strdup(envp[i]);
// 		if (!var)
// 		{
// 			while (i--)
// 				free(g_shell.envp[i]);
// 			free(g_shell.envp);
// 			return (EXIT_FAILURE);
// 		}
// 		g_shell.envp[i] = var;
// 	}
// 	return (EXIT_SUCCESS);
// }

// void	free_env(void)
// {
// 	int	i;

// 	i = 0;
// 	while (g_shell.envp[i])
// 		free(g_shell.envp[i++]);
// 	free(g_shell.envp);
// 	g_shell.envp = NULL;
// }
