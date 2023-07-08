/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jmp_moves.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 21:18:45 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/08 21:19:03 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	move_col(int x)
{
	(void)ft_printf("\033[%dG", x);
}

void	move_home(void)
{
	(void)ft_printf("\033[H");
}

void	move_to(int x, int y)
{
	(void)ft_printf("\033[%d;%dH", y, x);
}
