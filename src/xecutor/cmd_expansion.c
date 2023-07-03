/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:13:47 by dlu               #+#    #+#             */
/*   Updated: 2023/07/03 22:29:12 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ENVNAME_MAX	64

/* Get the next environment variable name and return how many characters
 * the pointer should be moved, excluding the increment in the loop. */
static int	get_envname(char *s, char *name)
{
	int	i;

	if (!s || *s != '$')
		return (0);
	if (s[1] == '?')
	{
		name[0] = '?';
		name[1] = '\0';
		return (2);
	}
	i = 0;
	while (s[++i] && (ft_isalnum(s[i]) || s[i] == '_') && i < ENVNAME_MAX)
		name[i - 1] = s[i];
	name[i - 1] = '\0';
	return (i);
}

/* Put the value of environment varibale and increment the pointers. */
static void	put_envvalue(char *arg, char *ret, int *i, int *j)
{
	char	*temp;
	char	env_name[ENVNAME_MAX];

	*i += get_envname(&arg[*i], env_name) - 1;
	if (ft_strncmp(env_name, "?", 1) == 0)
	{
		temp = ft_itoa(g_shell.status);
		*j = ft_strlcat(ret, temp, BUFFER_SIZE);
		free(temp);
	}
	else if (getenv(env_name))
		*j = ft_strlcat(ret, getenv(env_name), BUFFER_SIZE);
}

/* Expand a single token. */
// Statically defined for now, maybe change to dynamic later on.
char	*arg_expansion(char *arg)
{
	char	*ret;
	char	quote;
	int		i;
	int		j;

	ret = (char *) ft_calloc(BUFFER_SIZE, sizeof(char));
	if (!ret)
		return (NULL);
	i = -1;
	j = 0;
	quote = '\0';
	while (arg[++i] && j < BUFFER_SIZE - 1)
	{
		if (!quote && (arg[i] == '\'' || arg[i] == '"'))
			quote = arg[i];
		else if (quote && quote == arg[i])
			quote = '\0';
		else if ((!quote || quote == '"') && arg[i] == '$')
			put_envvalue(arg, ret, &i, &j);
		else
			ret[j++] = arg[i];
	}
	return (ret);
}

/* Expand the arguments for $. */
// This ideally would be after forking?
char	**cmd_expansion(char **args)
{
	char	**ret;
	int		i;

	ret = (char **) malloc((ft_strarrlen(args) + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	ret[ft_strarrlen(args)] = NULL;
	i = -1;
	while (args[++i])
	{
		ret[i] = arg_expansion(args[i]);
		if (!ret[i])
		{
			while (--i >= 0)
				free(ret[i]);
			return (NULL);
		}
	}
	return (ret);
}

/*
int	main(void)
{
	char *test[] = {"askdf\'$HOME\'$MAIL", "test$HOME", NULL};
	char **test2 = cmd_expansion(test);
	int i = -1;
	while (test2[++i])
		ft_printf("%s\n", test2[i]);
	return (0);
}*/
