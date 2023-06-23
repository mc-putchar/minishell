/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 10:29:20 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/23 15:45:49 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*new_cmd(char **tokens, int *i)
{
	t_cmd	*cmd;
	int		j;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = malloc(sizeof(char *) * MAX_ARGS);
	if (!cmd->args)
		return (NULL);
	j = 0;
	while (tokens[*i] && ft_strncmp(tokens[*i], "|", 1) && \
		ft_strncmp(tokens[*i], "<", 1) && ft_strncmp(tokens[*i], ">", 1) && \
		ft_strncmp(tokens[*i], ">>", 2) && ft_strncmp(tokens[*i], "<<", 2) && \
		ft_strncmp(tokens[*i], "&&", 2) && ft_strncmp(tokens[*i], "||", 2))
	{
		cmd->args[j] = ft_strdup(tokens[*i]);
		j++;
		(*i)++;
	}
	cmd->args[j] = NULL;
	return (cmd);
}

t_cmd	*new_cmd_table(t_cmd *cmd, int type, t_cmd *left, t_cmd *right)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	(void) cmd;
	//new->cmd = cmd;
	new->type = type;
	new->left = left;
	new->right = right;
	return (new);
}

int	get_cmd_type(t_cmd *cmd)
{
	if (!cmd->args[0])
		return (EMPTY);
	if (cmd->args[0][0] == '|')
		return (PIPE);
	else if (ft_strchr(cmd->args[0], '<'))
		return (REDIR_IN);
	else if (ft_strchr(cmd->args[0], '>'))
		return (REDIR_OUT);
	else if (!ft_strncmp(cmd->args[0], ">>", 2))
		return (REDIR_APPEND);
	else if (!ft_strncmp(cmd->args[0], "<<", 2))
		return (REDIR_HERE);
	else if (!ft_strncmp(cmd->args[0], "&&", 2))
		return (AND);
	else if (!ft_strncmp(cmd->args[0], "||", 2))
		return (OR);
	else
		return (CMD);
}

// TODO: implement free function
t_cmd	*parser(char **tokens)
{
	t_cmd	*cmd_tab;
	t_cmd	*prev;
	t_cmd	*cmd;
	int		i;
	int		type;

	i = 0;
	prev = NULL;
	while (tokens[i])
	{
		cmd = new_cmd(tokens, &i);
		type = get_cmd_type(cmd);
		cmd_tab = new_cmd_table(cmd, type, NULL, NULL);
		if (prev)
			prev->right = cmd_tab;
		prev = cmd_tab;
		if (type == PIPE || type == REDIR_IN || type == REDIR_OUT || \
			type == REDIR_APPEND || type == REDIR_HERE)
			i++;
	}
	return (cmd_tab);
}
