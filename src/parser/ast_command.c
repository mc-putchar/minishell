/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 19:34:30 by dlu               #+#    #+#             */
/*   Updated: 2023/06/24 09:02:20 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_arg_to_cmd(char *arg, t_cmd *cmd)
{
	int	i;

	i = -1;
	while (cmd->args[++i] && i < MAX_ARGS)
		;
	if (i < MAX_ARGS)
		cmd->args[i] = arg;
}

t_cmd	*build_command(void)
{
	t_cmd	*node;
	t_cmd	*temp;

	node = NULL;
	temp = NULL;
	if (g_shell.parse_error)
		return (NULL);
	if (accept(LPARENT))
	{
		node = build_conditional();
		if (!accept(RPARENT))
			return (free(node), ft_perror("Parser: parentheses"), NULL);
	}
	else if (expect(WORD))
	{
		node = new_cmd(COMMAND);
		while (expect(WORD))
		{
			append_arg_to_cmd(g_shell.tok->value, node);
			accept(WORD);
		}
	}
	return (node);
}
