/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 13:19:39 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/07 03:38:00 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO: add check for long paths and shorten them
char	*compact_cwd(char *cwd, char *home)
{
	char	*compact;

	if (ft_strncmp(cwd, home, ft_strlen(home)) == 0)
	{
		compact = ft_strjoin("~", cwd + ft_strlen(home));
		free(cwd);
		return (compact);
	}
	return (cwd);
}

// TODO: switch to local env once implemented
int	print_prompt(char *prompt)
{
	char	*user;
	char	*host;
	char	*cwd;

	if (prompt)
		return (ft_printf("%s", prompt), EXIT_SUCCESS);
	user = getenv("USER");
	host = getenv("HOST");
	cwd = malloc(BUFFER_SIZE);
	if (!cwd)
		return (EXIT_FAILURE);
	cwd = getcwd(cwd, BUFFER_SIZE);
	if (!cwd)
		return (EXIT_FAILURE);
	cwd = compact_cwd(cwd, getenv("HOME"));
	if (!host)
		host = "localhost";
	if (ft_printf("\r%s%s"MISH"%s:%s%s$ ", \
		BGCYAN MAGENTA, user, host, cwd, RESET) < 0)
		return (free(cwd), EXIT_FAILURE);
	free(cwd);
	return (EXIT_SUCCESS);
}
