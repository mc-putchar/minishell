/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 13:19:39 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/16 17:13:40 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO: add check for long paths and shorten them
char	*compact_cwd(char *cwd)
{
	char			*compact;
	char			*tmp;
	size_t const	homelen = ft_strlen(g_shell.home);

	if (!ft_strncmp(cwd, g_shell.home, homelen))
	{
		compact = ft_strjoin("~", cwd + homelen);
		free(cwd);
		cwd = compact;
	}
	if (ft_strlen(cwd) > 21 && ft_strrchr(cwd, '/'))
	{
		tmp = ft_strrchr(cwd, '/');
		compact = ft_strdup(tmp + 1);
		free(cwd);
		cwd = compact;
	}
	return (cwd);
}

int	print_prompt(char *prompt)
{
	char	*user;
	char	*host;
	char	*cwd;

	if (prompt)
		return (ft_printf("%s", prompt), EXIT_SUCCESS);
	user = ft_getenv("USER");
	host = ft_getenv("HOSTNAME");
	cwd = NULL;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (EXIT_FAILURE);
	cwd = compact_cwd(cwd);
	if (!user)
		user = "mish";
	if (!host)
		host = "localhost";
	if (ft_printf("%s%s"MISH"%s:%s%s$ ", \
	BGCYAN MAGENTA, user, host, cwd, RESET) < 0)
		return (free(cwd), EXIT_FAILURE);
	return (free(cwd), EXIT_SUCCESS);
}
