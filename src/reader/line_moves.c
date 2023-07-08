/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_moves.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 19:48:14 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/08 21:18:57 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	move_up(int x)
{
	(void)ft_printf("\033[%dA", x);
}

void	move_down(int x)
{
	(void)ft_printf("\033[%dB", x);
}

void	move_right(int x)
{
	(void)ft_printf("\033[%dC", x);
}

void	move_left(int x)
{
	(void)ft_printf("\033[%dD", x);
}
