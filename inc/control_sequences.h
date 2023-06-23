/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_sequences.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 07:21:52 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/22 12:48:53 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROL_SEQUENCES_H
# define CONTROL_SEQUENCES_H

# define BACKSPACE		'\177'
# define ENTER			'\012'
# define CTRL_C			'\003'
# define CTRL_D			'\004'
# define CTRL_L			'\014'
# define CTRL_R			'\022'
# define ESCAPE			'\033'
# define CTRL_BACKSLASH	'\034'
# define ARROW_UP		0x415B1B
# define ARROW_DOWN		0x425B1B
# define ARROW_RIGHT	0x435B1B
# define ARROW_LEFT		0x445B1B
# define DELETE			0x7E335B1B

# define MOVE_LEFT(x)	(void)ft_dprintf(STDOUT_FILENO, "\033[%dD", x)
# define MOVE_RIGHT(x)	(void)ft_dprintf(STDOUT_FILENO, "\033[%dC", x)
# define MOVE_COL(x)	(void)ft_dprintf(STDOUT_FILENO, "\033[%dG", x)
# define CLEAR_LINE		(void)ft_dprintf(STDOUT_FILENO, "\033[2K")
# define CLEAR_REST		(void)ft_dprintf(STDOUT_FILENO, "\033[0J")
# define CLEAR_SCREEN	(void)ft_dprintf(STDOUT_FILENO, "\033[2J")
# define MOVE_HOME		(void)ft_dprintf(STDOUT_FILENO, "\033[H")

#endif
