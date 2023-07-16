/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_basic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:48:28 by dlu               #+#    #+#             */
/*   Updated: 2023/07/16 17:22:35 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Create a new command node of a given type. */
t_cmd	*new_cmd(t_type type)
{
	t_cmd	*cmd;
	int		i;

	cmd = (t_cmd *) malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	i = -1;
	while (++i < MAX_ARGS)
		cmd->args[i] = NULL;
	cmd->type = type;
	cmd->pipe = NULL;
	cmd->i_file = NULL;
	cmd->o_file = NULL;
	cmd->o_type = EMPTY;
	cmd->i_type = EMPTY;
	cmd->left = NULL;
	cmd->right = NULL;
	cmd->here_doc = -1;
	cmd->execute = true;
	return (cmd);
}

/* Accept the next token only when it's the correct type. 
 * Will set parser error to true. */
bool	accept(t_type type)
{
	if (!expect(type))
		return (false);
	g_shell.tok = g_shell.tok->next;
	return (true);
}

/* Check if the current token is of a given type. */
bool	expect(t_type type)
{
	if (g_shell.tok && g_shell.tok->type == type)
		return (true);
	return (false);
}

/* Free the entire AST tree. */
void	free_cmd_ast(t_cmd *root)
{
	t_cmd	*temp;
	t_cmd	*tofree;

	if (!root)
		return ;
	free_cmd_ast(root->left);
	free_cmd_ast(root->right);
	temp = root->pipe;
	while (temp)
	{
		tofree = temp;
		temp = temp->pipe;
		free(tofree);
	}
	free(root);
}

/* Check if the current token is the redirection token. */
bool	expect_redir(void)
{
	return (expect(REDIR_IN) || expect(REDIR_OUT)
		|| expect(APPEND) || expect(HERE_DOC));
}
