/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 01:11:42 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/18 22:55:43 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_TABLE_H
# define CMD_TABLE_H

# define EMPTY			0
# define PIPE			1
# define REDIR_IN		2
# define REDIR_OUT		3
# define REDIR_APPEND	4
# define REDIR_HERE		5
# define AND			6
# define OR				7
# define BUILTIN		8
# define CMD			9

typedef struct s_cmd
{
	char				**args;
}	t_cmd;

typedef struct s_cmd_table
{
	t_cmd				*cmd;
	int					type;
	struct s_cmd_table	*left;
	struct s_cmd_table	*right;
}	t_cmd_table;

#endif
