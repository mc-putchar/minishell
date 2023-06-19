/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 10:28:59 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/19 17:00:58 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		lexer(char *line)
{
	char	**tokens;
	int		i;
	t_cmd	*cmd;

	i = 0;
	tokens = ft_split_blocks(line, ' ', "\'\"");
	if (!tokens)
		return (EXIT_FAILURE);
	// while (tokens[i])
	// {
	// 	ft_printf("\r\nToken %d: %s\n\r", i, tokens[i]);
	// 	++i;
	// }
	cmd = parser(tokens);
	if (!cmd)
		return (EXIT_FAILURE);
	while (cmd)
	{
		i = 0;
		while (cmd->args[i])
		{
			ft_printf("\r\nArg %d: %s\n\r", i, cmd->args[i]);
			++i;
		}
		ft_printf("\r\nType: %d\n\r", cmd->type);
		cmd = cmd->right;
	}
	return (EXIT_SUCCESS);
}
