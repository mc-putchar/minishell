/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 09:15:17 by dlu               #+#    #+#             */
/*   Updated: 2023/07/15 15:34:17 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void ast_display(t_cmd *node, int level)
// {
// 	if (node == NULL)
// 		return ;
// 	for (int i = 0; i < level; i++)
// 		ft_printf("\t");
// 	if (node->type == COMMAND) {
// 		ft_printf("Type: %d, Args: ", node->type);
// 		int	i = -1;
// 		while (node->args[++i] && i < MAX_ARGS)
// 			ft_printf("%s ", node->args[i]);
// 		ft_printf("\n");
// 		if (node->i_file)
// 			ft_printf("i_file: %s, type: %d\n", node->i_file, node->i_type);
// 		if (node->o_file)
// 			ft_printf("o_file: %s, type: %d\n", node->o_file, node->o_type);
// 		while (node->pipe)
// 		{
// 			ft_printf("	Pipe; Args: ");
// 			node = node->pipe;
// 			i = -1;
// 			while (node->args[++i] && i < MAX_ARGS)
// 				ft_printf("%s ", node->args[i]);
// 			ft_printf("\n");
// 			if (node->i_file)
// 				ft_printf("i_file: %s, type: %d\n", node->i_file, node->i_type);
// 			if (node->o_file)
// 				ft_printf("o_file: %s, type: %d\n", node->o_file, node->o_type);
// 		}
// 	} else {
// 		ft_printf("Type: %d\n", node->type);
// 	}
// 	ast_display(node->left, level + 1);
// 	ast_display(node->right, level + 1);
// }
