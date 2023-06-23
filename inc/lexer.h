/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:29:45 by dlu               #+#    #+#             */
/*   Updated: 2023/06/23 18:06:23 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef struct s_cmd	t_cmd;
typedef struct s_token	t_token;
typedef struct s_node	t_node;
typedef enum e_type		t_type;

enum e_type
{
	EMPTY,
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

struct s_token
{
	t_type	type;
	char	*value;
	t_token	*prev;  // Might be useless
	t_token	*next;
};

struct s_node
{
	t_type	type; // AND, OR, PIPE, COMMAND
	t_node	*left;
	t_node	*right;
	t_cmd	*cmd;
};

#endif
