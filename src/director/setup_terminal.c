/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_terminal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 13:22:49 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/06 02:25:05 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Print terminal settings
// void	print_term(struct termios *term)
// {
// 	ft_printf("c_iflag: %d\n", term->c_iflag);
// 	ft_printf("c_oflag: %d\n", term->c_oflag);
// 	ft_printf("c_cflag: %d\n", term->c_cflag);
// 	ft_printf("c_lflag: %d\n", term->c_lflag);
// 	ft_printf("c_cc: %d\n", term->c_cc);
// 	ft_printf("c_ispeed: %d\n", term->c_ispeed);
// 	ft_printf("c_ospeed: %d\n", term->c_ospeed);
// }

int	setup_terminal(struct termios *term_backup)
{
	struct termios	term;
	char			*name_term;

	name_term = getenv("TERM");
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

void	reset_terminal(struct termios *term_backup)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, term_backup) == -1)
		ft_perror("tcsetattr");
}
