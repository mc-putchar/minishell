/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 19:34:30 by dlu               #+#    #+#             */
/*   Updated: 2023/07/06 09:43:45 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Accept next word as argument. Move token forward. */
bool	append_arg_to_cmd(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (cmd->args[++i] && i < MAX_ARGS)
		;
	if (i >= MAX_ARGS)
		return (g_shell.parse_error = true, false);
	cmd->args[i] = g_shell.tok->value;
	return (accept(WORD));
}

t_cmd	*build_command(void)
{
	t_cmd	*node;

	node = NULL;
	if (accept(LPARENT))
	{
		node = build_conditional();
		accept(RPARENT);
	}
	else if (expect(WORD) || expect_redir())
	{
		node = new_cmd(COMMAND);
		if (!node)
			return (ft_perror("malloc"), NULL);
		while (expect(WORD) || expect_redir())
		{
			if (expect(WORD) && !append_arg_to_cmd(node))
				return (ft_perror("building command: too many args"), node);
			else
				load_redir(node);
		}
	}
	else
		return (g_shell.parse_error = true, new_cmd(EMPTY));
	return (node);
}
