/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:13:47 by dlu               #+#    #+#             */
/*   Updated: 2023/07/17 11:36:26 by mcutura          ###   ########.fr       */
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

/* Get the value of command line argument passed to program */
static int	get_argvalue(char *arg, char *ret, int *i, int *j)
{
	int		ac;
	char	*temp;

	if (!arg[*i + 1] || arg[*i + 1] == ' ' || (!ft_isalnum(arg[*i + 1]) && \
		(arg[*i + 1] != '_') && arg[*i + 1] != '?' && arg[*i + 1] != '"' && \
		arg[*i + 1] != '\''))
	{
		ret[(*j)++] = '$';
		return (1);
	}
	if (*i && arg[*i - 1] == '\\')
	{
		ret[*j - 1] = '$';
		return (1);
	}
	if (ft_isdigit(arg[*i + 1]))
	{
		ac = arg[(*i)++ + 1] - '0';
		if (ac > g_shell.ac - 1)
			return (1);
		temp = ft_strdup(g_shell.av[ac]);
		*j = ft_strlcat(ret, temp, BUFFER_SIZE);
		return (free(temp), 1);
	}
	return (0);
}

/* Put the value of environment varibale and increment the pointers. */
static void	put_envvalue(char *arg, char *ret, int *i, int *j)
{
	char	*temp;
	char	env_name[ENVNAME_MAX];

	if (get_argvalue(arg, ret, i, j))
		return ;
	*i += get_envname(&arg[*i], env_name) - 1;
	if (ft_strncmp(env_name, "?", 1) == 0)
	{
		temp = ft_itoa2(g_shell.status);
		*j = ft_strlcat(ret, temp, BUFFER_SIZE);
		free(temp);
	}
	else if (getenv(env_name))
		*j = ft_strlcat(ret, getenv(env_name), BUFFER_SIZE);
}

/* Expand a single token. */
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
		else if (!quote && arg[i] == '*')
			ret[j++] = (char) WC_CHAR;
		else
			ret[j++] = arg[i];
	}
	return (ret);
}

/* Expand the arguments for environment variables and wildcards. */
char	**cmd_expansion(char **args)
{
	char	**ret;
	int		i;
	int		j;

	ret = (char **) malloc(MAX_ARG_E * sizeof(char *));
	if (!ret)
		return (NULL);
	i = -1;
	j = 0;
	while (args[++i])
	{
		ret[j] = arg_expansion(args[i]);
		if (!ret[j])
		{
			while (--j >= 0)
				free(ret[i]);
			return (NULL);
		}
		if (ft_strchr(ret[j], WC_CHAR))
			j = wildcard_expansion(ret, ret[j], j);
		else
			++j;
	}
	ret[j] = NULL;
	return (ret);
}
