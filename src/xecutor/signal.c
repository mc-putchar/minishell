/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:14:57 by dlu               #+#    #+#             */
/*   Updated: 2023/07/07 16:38:58 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Empty signal handle, prints a new line. */
void	signal_handler(int signum)
{
	if (signum == SIGINT || signum == SIGQUIT || signum == SIGTSTP)
		ft_printf("\n");
}

/* Suspend the signal handlers until child process returns. */
void	signal_suspend(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	signal(SIGTSTP, signal_handler);
}

/* Restore the default signal handlers. */
void	signal_restore(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
}
