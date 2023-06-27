/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:13:47 by dlu               #+#    #+#             */
/*   Updated: 2023/06/27 18:44:39 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ENVNAME_MAX	50

/* Get the next environment variable name and return how many characters
 * the pointer should be moved. */
static int get_envname(char *s, char *name)
{
	int	i;

	if (!s || *s != '$')
		return (0);
	i = 0;
	while (s[++i] && (ft_isalnum(s[i]) || s[i] == '_'))
		name[i - 1] = s[i];
	name[i - 1] = '\0';
	return (i);
}

/* */
// Statically defined for now, maybe change to dynamic later on.
char	*arg_expansion(char *arg)
{
	char	env_name[ENVNAME_MAX];
	char	*ret;
	int		i;

	if (arg[0] == '\'')
		return (ft_substr(arg, 1, ft_strlen(arg) - 2));
	ret = (char *) ft_calloc(BUFFER_SIZE, sizeof(char));
	if (!ret)
		return (NULL);
	env_name = NULL;
	if (arg[0] == '"')
	{
		i = -1;
		while (arg[++i] && arg[i] != '"')
		{
			if (arg[i] == '$')
				i += get_envname(arg, env_name);
			
			ret[i] = arg[i + 1];
		}
	}
}

/* Expand the arguments for $. */
// This ideally would be after forking?
// Dynamic memory allocation would be a pain...
char	**cmd_expansion(char **args)
{
	char	**ret;
	int		i;
	
	ret = (char **) malloc((ft_strarrlen(args) + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	ret[ft_strarrlen(args)] = NULL;
	i = 0;
	while (args[++i])
	{
	}
	return (ret);
}
