/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:00:35 by dlu               #+#    #+#             */
/*   Updated: 2023/07/06 16:30:50 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Parse the entire cli then execute. */
int	parse_execute(char *line)
{
	if (!input_validator((const char *) line))
		return (EXIT_FAILURE);
	g_shell.tok_head = input_lexer(line);
	g_shell.tok = g_shell.tok_head;
	g_shell.parse_error = false;
	g_shell.ast = build_conditional();
	if (!g_shell.parse_error)
		executor(g_shell.ast);
	else
		ft_perror("parser error");
	free_cmd_ast(g_shell.ast);
	g_shell.ast = NULL;
	free_token(g_shell.tok_head);
	g_shell.tok_head = NULL;
	return (EXIT_SUCCESS);
}
