/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 03:17:04 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/16 17:57:17 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define HEADER	"🐭 mish 🐭 Miniature Interactive Shell"
#define AUTHORS	"Made with 💚 by dlu & mcutura"
#define ABOUT1	"minishell 🐭 is a miniature interactive shell"
#define ABOUT2	"made as a project for 42cursus @ 42berlin."
#define USAGE	"Usage: ./minishell"
#define AVAIL	"These commands are defined internally: \r\n\
		cd, echo, env, exit, export, help, pwd, unset\r\n"
#define DISCL	"DISCLAIMER: no leaks were harmed in the making of this shell."
#define WARANTY	"NO WARRANTY: this shell is provided 'as is' without warranty."

int	builtin_help(t_cmd *cmd)
{
	int	fds[2];

	backup_stdfds(fds);
	if (!redir_setup(cmd))
		return (EXIT_FAILURE);
	if (!cmd->execute)
		return (EXIT_FAILURE);
	(void) ft_printf("\
                  .--,       .--,\n\
                 ( (  \\.---./  ) )\n\
                  '.__/o   o\\__.'\n\
                     {=  ^  =}\n\
                      >  -  <\n\
       _____________.""`-------`"".________________\n\
      /  o%30sO      \\\n\
      \\ %42s /\n\
      /  .    O%28so   \\\n\
      \\ %38s /         __\n\
      / %40s \\     _.-'  `.\n\
      \\______________o__________o______________/ .-~^        `~--'\n\
                    ___)( )(___        `-._____.'\n\
                   (((__) (__)))", " ", HEADER, " ", " ", AUTHORS);
	(void)ft_printf("\r\n\r\n%s\r\n%s\r\n\r\n%s\r\n%s\r\n%s\r\n%s\r\n", \
		ABOUT1, ABOUT2, USAGE, AVAIL, DISCL, WARANTY);
	return (restore_stdfds(fds), EXIT_SUCCESS);
}
