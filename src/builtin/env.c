/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 18:29:22 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/08 21:16:20 by mcutura          ###   ########.fr       */
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
	var = ft_strjoin(name, "=");
	if (!var)
		return (EXIT_FAILURE);
	str = ft_strjoin(var, value);
	if (!str)
		return (free(var), EXIT_FAILURE);
	free(g_shell.envp[i]);
	g_shell.envp[i] = str;
	return (free(var), EXIT_SUCCESS);
}
