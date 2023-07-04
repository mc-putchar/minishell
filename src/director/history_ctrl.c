/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_ctrl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 12:44:17 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/04 10:57:23 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_end_history(t_cmdline *cmdl)
{
	if (cmdl->hist)
	{
		cmdl->size = ft_strlen(cmdl->hist);
		(void)ft_memcpy(cmdl->buff, cmdl->hist, cmdl->size);
		cmdl->buff[cmdl->size] = 0;
		free(cmdl->hist);
		cmdl->hist = NULL;
	}
	else
		cmdl->size = 0;
	CLEAR_LINE;
	MOVE_COL(0);
	if (print_prompt())
		ft_perror("print_prompt");
	ft_printf("%s", cmdl->buff);
	cmdl->i = cmdl->size;
	return ;
}

void	ctrl_down_history(t_cmdline *cmdl)
{
	t_list	*tmp;
	char	*line;

	if (!g_shell.hist || !g_shell.hist_i)
		return ;
	if (g_shell.hist_i-- == 1)
	{
		ctrl_end_history(cmdl);
		return ;
	}
	tmp = ft_lstget_atindex(g_shell.hist, g_shell.hist_i - 1);
	if (!tmp)
		return ;
	line = tmp->content;
	cmdl->buff[cmdl->size] = 0;
	(void)ft_memcpy(cmdl->buff, line, ft_strlen(line));
	CLEAR_LINE;
	MOVE_COL(0);
	if (print_prompt())
		ft_perror("print_prompt");
	ft_printf("%s", line);
	cmdl->i = cmdl->size;
}

void	ctrl_up_history(t_cmdline *cmdl)
{
	t_list	*tmp;

	if (!g_shell.hist)
		return ;
	if (ft_lstsize(g_shell.hist) > g_shell.hist_i)
	{
		tmp = ft_lstget_atindex(g_shell.hist, g_shell.hist_i);
		if (!tmp)
			return ;
		if (!g_shell.hist_i++)
		{
			cmdl->buff[cmdl->size] = 0;
			cmdl->hist = ft_strdup(cmdl->buff);
			if (!cmdl->hist)
				return ;
		}
		CLEAR_LINE;
		MOVE_COL(0);
		if (print_prompt())
			ft_perror("print_prompt");
		ft_printf("%s", tmp->content);
		cmdl->size = ft_strlen(tmp->content);
		(void)ft_memcpy(cmdl->buff, tmp->content, cmdl->size);
		cmdl->i = cmdl->size;
	}
}
