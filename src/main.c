/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 11:12:06 by dlu               #+#    #+#             */
/*   Updated: 2023/07/17 10:04:52 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_shell;

/* Setup environment variables. */
static bool	env_setup(char **ev)
{
	int		i;
	char	*lvl;
	char	*tmp;

	g_shell.envp = (char **) ft_calloc(sizeof(char *), MAX_ENV);
	if (!g_shell.envp)
		return (false);
	i = -1;
	while (ev[++i])
		g_shell.envp[i] = ft_strdup(ev[i]);
	__environ = g_shell.envp;
	g_shell.home = ft_getenv("HOME");
	if (!g_shell.home)
		g_shell.home = "/";
	lvl = ft_getenv("SHLVL");
	if (lvl)
	{
		tmp = ft_itoa2(ft_atoi(lvl) + 1);
		ft_setenv("SHLVL", tmp, 1);
		free(tmp);
	}
	else
		ft_setenv("SHLVL", "1", 1);
	ft_setenv("SHELL", "minishell", 1);
	return (true);
}

int	main(int ac, char **av, char **ev)
{
	int	status;

	g_shell.ac = ac;
	g_shell.av = av;
	if (!env_setup(ev))
		return (EXIT_FAILURE);
	status = director(ac, av);
	return (status);
}
