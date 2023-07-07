/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_terminal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 13:22:49 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/07 14:54:48 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_terminal(t_termios *term_backup)
{
	t_termios	term;
	char		*name_term;

	name_term = ft_getenv("TERM");
	if (!name_term || tcgetattr(STDIN_FILENO, term_backup) == -1 || \
		tcgetattr(STDIN_FILENO, &term) == -1)
		return (ENOTTY);
	term.c_iflag &= ~(IGNBRK | BRKINT | INLCR | IGNCR | ICRNL | IXON);
	term.c_lflag &= ~(ICANON | ECHO | ECHONL | ISIG | IEXTEN);
	term.c_cflag &= ~(CSIZE | PARENB);
	term.c_cflag |= CS8;
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		return (ENOTTY);
	return (EXIT_SUCCESS);
}

void	reset_terminal(t_termios *term_backup)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, term_backup) == -1)
		ft_perror("tcsetattr");
}
