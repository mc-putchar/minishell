/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:00:35 by dlu               #+#    #+#             */
/*   Updated: 2023/07/07 10:46:46 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ERR_PAREN	"parenthese only support priority next to logical operators"

/* Check pipeline does not contain control structures. */
static bool	pipe_check(t_cmd *cmd)
{
	t_cmd	*temp;

	if (!cmd)
		return (true);
	if (cmd->type == COMMAND)
	{
		temp = cmd->pipe;
		while (temp)
		{
			if (temp->type != COMMAND)
				return (false);
			temp = temp->pipe;
		}
	}
	return (pipe_check(cmd->left) && pipe_check(cmd->right));
}

/* Check parentheses are only next to logical operators. */
static bool	paren_check(t_token *t)
{
	while (t)
	{
		if (t->type == LPARENT || t->type == RPARENT)
		{
			if ((t->prev && t->prev->type != AND && t->prev->type != OR)
				|| (t->next && t->next->type != AND && t->next->type != OR))
				return (ft_perror(ERR_PAREN), false);
		}
		t = t->next;
	}
	return (true);
}

/* Check syntax is valid. */
static bool	syntax_check(t_cmd *cmd, t_token *tok)
{
	return (pipe_check(cmd) && paren_check(tok));
}

/* Parse the entire cli then execute. */
int	parse_execute(char *line)
{
	if (!input_validator((const char *) line))
		return (EXIT_FAILURE);
	g_shell.tok_head = input_lexer(line);
	free(line);
	g_shell.tok = g_shell.tok_head;
	g_shell.parse_error = false;
	g_shell.ast = build_conditional();
	if (!g_shell.parse_error && syntax_check(g_shell.ast, g_shell.tok_head))
		executor(g_shell.ast);
	else
		ft_perror("parser error");
	free_cmd_ast(g_shell.ast);
	g_shell.ast = NULL;
	free_token(g_shell.tok_head);
	g_shell.tok_head = NULL;
	return (EXIT_SUCCESS);
}
