/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 11:12:06 by dlu               #+#    #+#             */
/*   Updated: 2023/06/17 11:39:35 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;
int			g_status;

int	main(int ac, char **av, char **ev)
{
	char	*input;
	
	// cpy & redirect environ
	while (ac && av && ev)
	{
		input = readline(PROMPT);
		ft_printf("%s\n", input);
		// parse args
		// execute cmd
		free(input);
	}
	return (EXIT_SUCCESS);
}
