/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:13:47 by dlu               #+#    #+#             */
/*   Updated: 2023/06/26 19:02:30 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Expand the arguments for $. */
// This ideally would be after forking?
// Dynamic memory allocation would be a pain...
char **cmd_expansion(char **args)
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
