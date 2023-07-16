/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_ctrl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 12:44:17 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/16 19:41:42 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_history_entry(int i, char *new, int size)
{
	t_list	*tmp;

	tmp = ft_lstget_atindex(g_shell.hist, i);
	if (!tmp)
		return ;
	free(tmp->content);
	new[size] = 0;
	tmp->content = ft_strdup(new);
}

void	ctrl_end_history(t_cmdline *cmdl, char *prompt)
{
	update_history_entry(g_shell.hist_i, cmdl->buff, cmdl->size);
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
	clear_line();
	move_col(0);
	if (print_prompt(prompt))
		ft_printf("%s%s", MISH, PROMPT);
	ft_printf("%s", cmdl->buff);
	cmdl->i = cmdl->size;
	return ;
}

void	ctrl_down_history(t_cmdline *cmdl, char *prompt)
{
	t_list	*tmp;
	char	*line;

	if (!g_shell.hist || !g_shell.hist_i)
		return ;
	if (g_shell.hist_i-- == 1)
	{
		ctrl_end_history(cmdl, prompt);
		return ;
	}
	cmdl->buff[cmdl->size] = 0;
	update_history_entry(g_shell.hist_i, cmdl->buff, cmdl->size);
	tmp = ft_lstget_atindex(g_shell.hist, g_shell.hist_i - 1);
	if (!tmp)
		return ;
	line = tmp->content;
	cmdl->size = ft_strlen(line);
	(void)ft_memcpy(cmdl->buff, line, cmdl->size);
	clear_line();
	move_col(0);
	if (print_prompt(prompt))
		ft_printf("%s%s", MISH, PROMPT);
	ft_printf("%s", line);
	cmdl->i = cmdl->size;
}

static void	reprint_prompt(char *prompt)
{
	clear_line();
	move_col(0);
	if (print_prompt(prompt))
		ft_printf("%s%s", MISH, PROMPT);
}

void	ctrl_up_history(t_cmdline *cmdl, char *prompt)
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
		else
			update_history_entry(g_shell.hist_i - 2, cmdl->buff, cmdl->size);
		reprint_prompt(prompt);
		ft_printf("%s", tmp->content);
		cmdl->size = ft_strlen(tmp->content);
		(void)ft_memcpy(cmdl->buff, tmp->content, cmdl->size);
		cmdl->i = cmdl->size;
	}
}
