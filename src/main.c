/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 11:12:06 by dlu               #+#    #+#             */
/*   Updated: 2023/06/24 07:45:04 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_shell;

int	main(int ac, char **av, char **ev)
{
	while (ac && av && ev)
		if (director(ac, av, ev))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
