/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 21:16:52 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/08 21:18:07 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_to_line_end(void)
{
	(void)ft_printf("\033[K");
}

void	clear_to_line_start(void)
{
	(void)ft_printf("\033[1K");
}

void	clear_line(void)
{
	(void)ft_printf("\033[2K");
}
