/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:29:45 by dlu               #+#    #+#             */
/*   Updated: 2023/06/24 11:39:17 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef struct s_cmd	t_cmd;
typedef struct s_token	t_token;
typedef struct s_node	t_node;
typedef enum e_type		t_type;

# define MAX_ARGS		255

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

struct s_cmd
{
	char	*args[MAX_ARGS]; // statically defined for now, may change to dynamic resize later
	t_type	type;
	t_cmd	*left;
	t_cmd	*right;
	t_cmd	*pipe;	//PIPE node will point to a cmd, each command will point to the next pipe
					//if NULL, standalone
	char	*i_file;
	char	*o_file;
	t_type	o_type; // APPEND / REDIR_OUT
	t_type	i_type; // HERE_DOC / REDIR_IN; seems like they can work simultaneously
};


struct s_token
{
	t_type	type;
	char	*value;
	t_token	*prev;  // Might be useless
	t_token	*next;
};

#endif
