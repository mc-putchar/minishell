/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 13:19:39 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/20 21:04:00 by dlu              ###   ########.fr       */
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

//TODO: maybe add user@host to prompt
char	*build_prompt(void)
{
	char	*cwd;
	char	*prompt;
	char	*tmp;

	cwd = malloc(BUFFER_SIZE);
	if (!cwd)
		return (NULL);
	cwd = getcwd(cwd, BUFFER_SIZE);
	if (!cwd)
		return (NULL);
	cwd = compact_cwd(cwd, getenv("HOME"));
	tmp = ft_strjoin(BGCYAN MAGENTA, cwd);
	free(cwd);
	prompt = ft_strjoin(tmp, RESET PROMPT);
	free(tmp);
	return (prompt);
}
