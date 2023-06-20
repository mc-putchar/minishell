/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   director.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 05:26:20 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/20 16:50:24 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	gtfo(char *prompt)
{
	free(prompt);
	ft_dprintf(STDOUT_FILENO, "\r\nbyeee!\r\n");
	exit(EXIT_SUCCESS);
}

void	reset_cmd_line(char *prompt, char *buff, int *i)
{
	*i = 0;
	ft_bzero(buff, BUFSIZ);
	ft_dprintf(STDOUT_FILENO, "\r\n%s", prompt);
}

int	director(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;
	if (init_shell())
		return (EXIT_FAILURE);
	if (do_stuff())
		ft_dprintf(STDERR_FILENO, "Error: do_stuff\n");
	return (EXIT_SUCCESS);
}
