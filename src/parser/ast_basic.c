/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_basic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:48:28 by dlu               #+#    #+#             */
/*   Updated: 2023/06/23 19:01:50 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Create a new node of a given type.
 * Handles pipe, and, or. */
t_node	*new_node(t_type type)
{
	t_node	*node;

	node = (t_node *) malloc(sizeof(t_node));
	node->type = type;
	return (node);
}

/* Accept the next token only when:
 * 1. there was no prior error.
 * 2. it's the correct type. 
 * Otherwise it returns NULL. */
t_node	*accept(t_type type)
{
	if (g_shell.parse_error || !expect(type))
		return (NULL);
	g_shell.current_tok = current_tok->next;
	return (new_node(type));
}

/* Check if the current token is of a given type. */
bool	expect(t_type type)
{
	if (g_shell.current_tok && g_shell.current_tok->type == type)
		return (true);
	return (false);
}
