/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_block.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:05:02 by dlu               #+#    #+#             */
/*   Updated: 2023/06/23 19:34:13 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * BNF
 *
 * <conditional>	::= 
 *						<pipeline>
 *					|	<pipeline> '&&' <conditional> 
 *					|	<pipeline> '||' <conditional>
 * <pipeline>		::= 
 *						<command>
 *					|	<command> '|' <pipeline>
 * <redirection>	::=
 *						'>' <word>
 *					|	'<' <word>
 *					|	'>>' <word>
 *					|	'<<' <word>
 * <command>		::=
 *						<word>
 *					|	<word> <command>
 *					|	<redirection>			// to implement
 *					|	<redirection> <command> // to implement
 *					|	<command> <redirection> // to implement
 *					|	'(' <conditional> ')'
 */

t_node	*build_conditional(void)
{
	t_node	*node;
	t_node	*temp;

	if (g_shell.parse_error)
		return (NULL);
	node = build_pipeline();
	while (expect(AND) || expect(OR))
	{
		if (expect(AND))
			temp = accept(AND);
		else
			temp = accept(OR);
		temp->left = node;
		temp->right = build_pipeline();
		node = temp;
	}
	return (node);
}

t_node	*build_pipeline(void)
{
	t_node	*node;
	t_node	*temp;

	if (g_shell.parse_error)
		return (NULL);
	node = build_command();
	while (expect(PIPE))
	{
		temp = accept(PIPE);
		temp->left = node;
		temp->right = build_command();
		node = temp;
	}
	return (node);
}
