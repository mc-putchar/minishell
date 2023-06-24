/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_basic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:48:28 by dlu               #+#    #+#             */
/*   Updated: 2023/06/24 11:31:55 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd(t_type type)
{
	t_cmd	*cmd;
	int		i;

	cmd = (t_cmd *) malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	i = -1;
	while (++i < MAX_ARGS)
		cmd->args[i] = NULL;
	cmd->type = type;
	cmd->pipe = NULL;
	cmd->i_file = NULL;
	cmd->o_file = NULL;
	cmd->o_type = EMPTY;
	cmd->i_type = EMPTY;
	cmd->left = NULL;
	cmd->right = NULL;
	return (cmd);
}

/* Create a new node of a given type.
 * Handles pipe, and, or.
t_node	*new_node(t_type type)
{
	t_node	*node;

	node = (t_node *) malloc(sizeof(t_node));
	node->type = type;
	init_cmd(&(node->cmd));
	return (node);
}*/

/* Accept the next token only when:
 * 1. there was no prior error.
 * 2. it's the correct type. 
 * Otherwise it returns NULL. */
bool	accept(t_type type)
{
	if (!expect(type))
		return (false);
	g_shell.tok = g_shell.tok->next;
	return (true);
}

/* Check if the current token is of a given type. */
bool	expect(t_type type)
{
	if (g_shell.tok && g_shell.tok->type == type)
		return (true);
	return (false);
}