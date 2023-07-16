/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_environ.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:09:02 by dlu               #+#    #+#             */
/*   Updated: 2023/07/16 19:33:08 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ERR_KEY	"%s: export: '%s': not a valid identifier\n"
#define ERR_MAX	"environment variable over limit"

/* Check if the env key is valid. */
static bool	envkey_valid(char *key)
{
	while (*key)
	{
		if (!(ft_isalnum(*key) || *key == '_'))
			return (false);
		++key;
	}
	return (true);
}

/* Unset, add, or replace a single environment variable. */
void	replace_env(char *key, char *replace)
{
	int		i;
	char	*temp;

	temp = ft_strjoin(key, "=");
	i = -1;
	while (g_shell.envp[++i])
		if (ft_strncmp(g_shell.envp[i], temp, ft_strlen(temp)) == 0)
			break ;
	free(g_shell.envp[i]);
	free(temp);
	if (replace)
		g_shell.envp[i] = ft_strdup(replace);
	else
	{
		while (g_shell.envp[i + 1])
		{
			g_shell.envp[i] = g_shell.envp[i + 1];
			++i;
		}
		g_shell.envp[i] = NULL;
	}
}

/* Assign environment variables. */
int	builtin_export(t_cmd *cmd)
{
	const char	**av = (const char **) cmd_expansion(cmd->args);
	char		**temp;
	int			i;
	int			status;

	i = 0;
	status = EXIT_SUCCESS;
	while (av[++i])
	{
		temp = ft_split(av[i], '=');
		if (!envkey_valid(temp[0]))
		{
			ft_dprintf(STDERR_FILENO, ERR_KEY, MISH, av[i]);
			ft_strarrfree(temp);
			status = EXIT_FAILURE;
			continue ;
		}
		if (!temp[1])
			return (ft_strarrfree((char **) av), EXIT_SUCCESS);
		if (ft_strarrlen(g_shell.envp) >= MAX_ENV)
			return (ft_strarrfree((char **) av), EXIT_FAILURE);
		replace_env(temp[0], (char *) av[i]);
		ft_strarrfree(temp);
	}
	return (ft_strarrfree((char **) av), status);
}

/* Unset all the environment variable key given as arguments. */
int	builtin_unset(t_cmd *cmd)
{
	const char	**av = (const char **) cmd_expansion(cmd->args);
	int			i;

	i = 0;
	while (av[++i])
		replace_env((char *) av[i], NULL);
	ft_strarrfree((char **) av);
	return (EXIT_SUCCESS);
}

int	builtin_env(t_cmd *cmd)
{
	int	i;
	int	fd[2];

	backup_stdfds(fd);
	if (!redir_setup(cmd))
		return (EXIT_FAILURE);
	if (!cmd->execute)
		return (EXIT_FAILURE);
	i = -1;
	while (g_shell.envp[++i] && cmd)
		ft_printf("%s\r\n", g_shell.envp[i]);
	restore_stdfds(fd);
	return (EXIT_SUCCESS);
}
