/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:29:45 by dlu               #+#    #+#             */
/*   Updated: 2023/07/16 17:26:05 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdbool.h>

typedef struct s_cmd	t_cmd;
typedef struct s_token	t_token;
typedef struct s_node	t_node;
typedef enum e_type		t_type;

# define MAX_ARGS		255

enum e_type
{
	EMPTY,
	INVALID,
	WORD,
	REDIR_IN,
	REDIR_OUT,
	HERE_DOC,
	APPEND,
	PIPE,
	AND,
	OR,
	LPARENT,
	RPARENT,
	COMMAND
};

struct s_cmd
{
	char	*args[MAX_ARGS];
	t_type	type;
	t_cmd	*left;
	t_cmd	*right;
	t_cmd	*pipe;
	char	*i_file;
	char	*o_file;
	t_type	o_type;
	t_type	i_type;
	int		here_doc;
	bool	execute;
};

struct s_token
{
	t_type	type;
	char	*value;
	t_token	*prev;
	t_token	*next;
};

#endif
