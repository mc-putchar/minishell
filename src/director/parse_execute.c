/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:00:35 by dlu               #+#    #+#             */
/*   Updated: 2023/07/05 22:07:57 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Parse the entire cli then execute. */
int	parse_execute(char *line)
{
	t_cmd	*ast;

	if (!input_validator((const char *) line))
		return (EXIT_FAILURE);
	g_shell.tok_head = input_lexer(line);
	g_shell.tok = g_shell.tok_head;
	g_shell.parse_error = false;
	// tokens_print(g_shell.tok_head);
	ast = build_conditional();
	// ast_display(ast, 0);
	if (!g_shell.parse_error)
		executor(ast);
	else
		ft_perror("parser error");
	free_cmd_ast(ast); // everything needs freeing needs to be in the global struct
					   // so that it can be freed when exit is being executed
	free_token(g_shell.tok_head);
	return (EXIT_SUCCESS);
}
