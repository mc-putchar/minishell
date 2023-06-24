/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_block.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:05:02 by dlu               #+#    #+#             */
/*   Updated: 2023/06/24 11:36:53 by dlu              ###   ########.fr       */
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

t_cmd	*build_conditional(void)
{
	t_cmd	*node;
	t_cmd	*temp;

	node = build_pipeline();
	if (!node)
		return (ft_perror("building pipeline"), NULL);
	while (expect(AND) || expect(OR))
	{
		if (accept(AND))
			temp = new_cmd(AND);
		else if (accept(OR))
			temp = new_cmd(OR);
		temp->left = node;
		temp->right = build_pipeline();
		node = temp;
	}
	return (node);
}

t_cmd	*build_pipeline(void)
{
	t_cmd	*node;
	t_cmd	*temp;

	node = build_command();
	if (!node)
		return (ft_perror("building command"), NULL);
	temp = node;
	while (accept(PIPE))
	{
		while (temp->pipe)
			temp = temp->pipe;
		temp->pipe = build_command();
	}
	return (node);
}
