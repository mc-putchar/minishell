/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_sequences.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 07:21:52 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/20 16:45:01 by mcutura          ###   ########.fr       */
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

# define MOVE_LEFT(x)	ft_dprintf(STDOUT_FILENO, "\033[%dD", x)
# define MOVE_RIGHT(x)	ft_dprintf(STDOUT_FILENO, "\033[%dC", x)
# define CLEAR_LINE		ft_dprintf(STDOUT_FILENO, "\033[2K")
# define CLEAR_REST		ft_dprintf(STDOUT_FILENO, "\033[0J")
# define CLEAR_SCREEN	ft_dprintf(STDOUT_FILENO, "\033[2J")
# define MOVE_HOME		ft_dprintf(STDOUT_FILENO, "\033[H")

#endif
