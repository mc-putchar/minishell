/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_block.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:05:02 by dlu               #+#    #+#             */
/*   Updated: 2023/07/06 09:43:18 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * BNF
 *
 * <conditional>	::= 
 *						<pipeline>
 *					|	<pipeline> { '&&' <pipeline> }
 *					|	<pipeline> { '||' <pipeline> }
 * <pipeline>		::= 
 *						<command>
 *					|	<command> { '|' <command> }
 * <redirection>	::=
 *						'>' <word>
 *					|	'<' <word>
 *					|	'>>' <word>
 *					|	'<<' <word>
 * <command>		::=
 *						<word>
 *					|	<word> { <word> | <redirection> }
 *					|	<redirection> | { <word> | <redirection> }
 *					|	'(' <conditional> ')'
 */

/* Top level entry point to build an AST. */
t_cmd	*build_conditional(void)
{
	t_cmd	*node;
	t_cmd	*temp;

	node = build_pipeline();
	if (!node)
		return (NULL);
	while (expect(AND) || expect(OR))
	{
		if (accept(AND))
			temp = new_cmd(AND);
		else if (accept(OR))
			temp = new_cmd(OR);
		temp->left = node;
		temp->right = build_pipeline();
		if (!temp->right)
			g_shell.parse_error = true;
		node = temp;
	}
	return (node);
}

/* Attempt to build a pipeline. */
t_cmd	*build_pipeline(void)
{
	t_cmd	*node;
	t_cmd	*temp;

	node = build_command();
	if (!node)
		return (NULL);
	temp = node;
	while (accept(PIPE))
	{
		while (temp->pipe)
			temp = temp->pipe;
		temp->pipe = build_command();
		if (!temp->pipe)
			g_shell.parse_error = true;
	}
	return (node);
}
