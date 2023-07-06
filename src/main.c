/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 11:12:06 by dlu               #+#    #+#             */
/*   Updated: 2023/07/06 01:09:56 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_shell;

/* Setup environment variables. */
static bool	env_setup(char **ev)
{
	int	i;

	g_shell.envp = (char **) ft_calloc(sizeof(char *), MAX_ENV);
	if (!g_shell.envp)
		return (false);
	i = -1;
	while (ev[++i])
		g_shell.envp[i] = ft_strdup(ev[i]);
	__environ = g_shell.envp;
	return (true);
}

int	main(int ac, char **av, char **ev)
{
	if (!env_setup(ev))
		return (EXIT_FAILURE);
	while (ac && av && ev)
		if (director(ac, av, ev))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
