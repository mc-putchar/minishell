/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 19:34:18 by dlu               #+#    #+#             */
/*   Updated: 2023/06/24 11:33:42 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	load_redir(t_cmd *node)
{
	if (accept(REDIR_IN))
	{
		if (!expect(WORD))
			return (ft_perror("parser: redirection syntax"), false);
		node->i_file = g_shell.tok->value;
		node->i_type = REDIR_IN;
		return (accept(WORD));
	}
	else if (accept(REDIR_OUT))
	{
		if (!expect(WORD))
			return (ft_perror("parser: redirection syntax"), false);
		node->o_file = g_shell.tok->value;
		node->o_type = REDIR_OUT;
		return (accept(WORD));
	}
	else if (accept(APPEND))
	{
		if (!expect(WORD))
			return (ft_perror("parser: redirection syntax"), false);
		node->o_file = g_shell.tok->value;
		node->o_type = APPEND;
		return (accept(WORD));
	}
	else if (accept(HERE_DOC))
	{
		if (!expect(WORD))
			return (ft_perror("parser: redirection syntax"), false);
		node->i_file = g_shell.tok->value; // would be end token
		node->i_type = HERE_DOC;
		return (accept(WORD));
	}
	return (false);
}

bool	expect_redir(void)
{
	return (expect(REDIR_IN) || expect(REDIR_OUT) || expect(APPEND) || expect(HERE_DOC));
}
