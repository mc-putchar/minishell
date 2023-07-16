/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 19:34:18 by dlu               #+#    #+#             */
/*   Updated: 2023/07/16 17:22:09 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Handles '<' and '<<'. */
static bool	redir_in(t_cmd *node, t_type type)
{
	if (!expect(WORD))
		return (ft_perror("parser: redirection syntax"), false);
	node->i_file = g_shell.tok->value;
	node->i_type = type;
	if (type == HERE_DOC)
		node->here_doc = here_doc(node);
	return (accept(WORD));
}

/* Handles '>' and '>>'. */
static bool	redir_out(t_cmd *node, t_type type)
{
	if (!expect(WORD))
		return (ft_perror("parser: redirection syntax"), false);
	node->o_file = g_shell.tok->value;
	node->o_type = type;
	return (accept(WORD));
}

/* Load the redirection information into the structure. */
bool	load_redir(t_cmd *node)
{
	if (accept(REDIR_IN))
		return (redir_in(node, REDIR_IN));
	else if (accept(REDIR_OUT))
		return (redir_out(node, REDIR_OUT));
	else if (accept(APPEND))
		return (redir_out(node, APPEND));
	else if (accept(HERE_DOC))
		return (redir_in(node, HERE_DOC));
	return (false);
}
