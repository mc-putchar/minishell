/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_BNF.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:17:44 by dlu               #+#    #+#             */
/*   Updated: 2023/06/23 19:01:29 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Proof of concept, to rewrite
int	ft_next_len(char *input, char c)
{
	int	i;

	if (!c)
	{
		i = -1;
		while (input[++i] && !ft_ismeta(input[i]))
			;
		return (i);
	}
	else
	{
		i = 0;
		while (input[++i] && input[i] != c)
			;
		return (i + 1);
	}
}

/* Generate a doubly linked list of tokens. */
// Proof of concept, to refractor
// Doubly linked because I might want to try to parse from the right in the parser,
// and might be easier to free
t_token* input_lexer(char* input)
{
	t_token* start;
	t_token* last;
	char	quote;

	start = NULL;
	last = NULL;
	quote = 0;
	while (*input)
	{
		while (*input == ' ' || *input == '\t')
			++input;
		if (!*input)
			break ;
		if (ft_strncmp(input, "||", 2) == 0 && ++input && ++input)
			last = new_token(OR, NULL, last);
		else if (ft_strncmp(input, "&&", 2) == 0 && ++input && ++input)
			last = new_token(AND, NULL, last);
		else if (ft_strncmp(input, ">>", 2) == 0 && ++input && ++input)
			last = new_token(APPEND, NULL, last);
		else if (ft_strncmp(input, "<<", 2) == 0 && ++input && ++input)
			last = new_token(HERE_DOC, NULL, last);
		else if (*input == '<' && ++input)
			last = new_token(REDIR_IN, NULL, last);
		else if (*input == '>' && ++input)
			last = new_token(REDIR_OUT, NULL, last);
		else if (*input == '|' && ++input)
			last = new_token(PIPE, NULL, last);
		else if (*input == '(' && ++input)
			last = new_token(LPARENT, NULL, last);
		else if (*input == ')' && ++input)
			last = new_token(RPARENT, NULL, last);
		else if (*input == '\'')
		{
			last = new_token(WORD, ft_substr((const char *) input, 0, ft_next_len(input, '\'')), last);
			input += ft_next_len(input, '\'');
		}
		else if (*input == '"')
		{
			last = new_token(WORD, ft_substr((const char *) input, 0, ft_next_len(input, '"')), last);
			input += ft_next_len(input, '"');
		}
		else
		{
			last = new_token(WORD, ft_substr((const char *) input, 0, ft_next_len(input, 0)), last);
			input += ft_next_len(input, 0);
		}
		if (!start)
			start = last;
	}
	return (start);
}
/*
int	main(void)
{
	t_token *start = input_lexer(" ( ls |   \" cat  asdv\") && exit ");
	while (start)
	{
		ft_printf("%d %s\n", start->type, start->value);
		start = start->next;
	}
}*/
