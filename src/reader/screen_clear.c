/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 21:17:32 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/08 21:18:22 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_to_screen_end(void)
{
	(void)ft_printf("\033[J");
}

void	clear_to_screen_start(void)
{
	(void)ft_printf("\033[1J");
}

void	clear_terminal(void)
{
	(void)ft_printf("\033[2J");
}
