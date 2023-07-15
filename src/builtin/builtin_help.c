/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 03:17:04 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/15 03:38:41 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define HEADER	"		🐭 mish 🐭 Miniature Interactive Shell"
#define AUTHORS	"		Made with 💚 by dlu & mcutura"
#define ABOUT	"		minishell 🐭 is a miniature interactive shell \r\n\
		made as a project for 42cursus @ 42berlin.\r\n\
		Supports running in interactive mode only.\r\n"
#define USAGE	"		Usage: ./minishell"
#define AVAIL	"		These commands are defined internally: \r\n\
		cd, echo, env, exit, export, help, pwd, unset\r\n"

int	builtin_help(t_cmd *cmd)
{
	int	fds[2];

	backup_stdfds(fds);
	if (!redir_setup(cmd))
		return (EXIT_FAILURE);
	(void)ft_printf("\r\n%s\r\n\r\n%s\r\n\r\n%s\r\n%s\r\n\r\n%s\r\n", \
		HEADER, AUTHORS, ABOUT, USAGE, AVAIL);
	restore_stdfds(fds);
	return (EXIT_SUCCESS);
}
