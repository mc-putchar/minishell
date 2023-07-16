/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:00:35 by dlu               #+#    #+#             */
/*   Updated: 2023/07/16 17:05:11 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ERR_PAREN	"parenthese only support priority next to logical operators"

/* Check parentheses are only next to logical operators. */
static bool	paren_check(t_token *t)
{
	while (t)
	{
		if (t->type == LPARENT && (!t->prev || t->prev->type == LPARENT \
			|| t->prev->type == AND || t->prev->type == OR))
			t = t->next;
		else if (t->type == RPARENT && (!t->next || t->next->type == RPARENT \
			|| t->next->type == AND || t->next->type == OR))
			t = t->next;
		else if (t->type == LPARENT || t->type == RPARENT)
			return (ft_perror(ERR_PAREN), false);
		else
			t = t->next;
	}
	return (true);
}

/* Parse the entire cli then execute. */
int	parse_execute(char *line)
{
	if (!input_validator((const char *) line))
		return (free(line), EXIT_FAILURE);
	g_shell.tok_head = input_lexer(line);
	free(line);
	g_shell.tok = g_shell.tok_head;
	g_shell.parse_error = false;
	g_shell.ast = build_conditional();
	if (!g_shell.parse_error && paren_check(g_shell.tok_head))
		g_shell.status = executor(g_shell.ast);
	else
		ft_perror("parser error");
	free_cmd_ast(g_shell.ast);
	g_shell.ast = NULL;
	free_token(g_shell.tok_head);
	g_shell.tok_head = NULL;
	return (EXIT_SUCCESS);
}
