/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:48:57 by dlu               #+#    #+#             */
/*   Updated: 2023/07/04 17:21:20 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Execute the builtin command, all arguments should be expanded. 
// Permission, error message, input redirection has no effect */
// Redirection
int	builtin_echo(t_cmd *cmd)
{
	const char	**av = (const char **) cmd_expansion(cmd->args);
	const int	fd = 1;
	bool		n_flag;
	int			i;

	n_flag = false;
	i = 0;
	while (av[++i])
	{
		if (i == 1 && ft_strlen(av[i]) == 2 && ft_strncmp("-n", av[1], 2) == 0)
			n_flag = true;
		else if (av[i + 1])
		{
			write(fd, av[i], ft_strlen(av[i]));
			write(fd, " ", 1);
		}
		else if (!n_flag)
			ft_putendl_fd((char *) av[i], fd);
		else
			write(fd, av[i], ft_strlen(av[i]));
	}
	return (ft_strarrfree((char **) av), EXIT_SUCCESS);
}
