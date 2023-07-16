/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 10:28:59 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/16 17:04:02 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Return the length until next metacharacter, or quotes. */
static int	ft_next_len(char *input, char c)
{
	int	i;

	i = -1;
	if (!c)
	{
		while (input[++i] && !ft_ismeta(input[i]))
			if (input[i] == '"' || input [i] == '\'')
				i += ft_next_len(&input[i], input[i]) - 1;
	}
	else
	{
		++i;
		while (input[++i] && input[i] != c)
			;
		++i;
	}
	return (i);
}

/* Handles the operators for lexer. */
static void	handle_op(char **s, t_token **last)
{
	if (ft_strncmp(*s, "||", 2) == 0 && ++(*s) && ++(*s))
		*last = new_token(OR, "||", *last);
	else if (ft_strncmp(*s, "&&", 2) == 0 && ++(*s) && ++(*s))
		*last = new_token(AND, "&&", *last);
	else if (ft_strncmp(*s, ">>", 2) == 0 && ++(*s) && ++(*s))
		*last = new_token(APPEND, ">>", *last);
	else if (ft_strncmp(*s, "<<", 2) == 0 && ++(*s) && ++(*s))
		*last = new_token(HERE_DOC, "<<", *last);
	else if (**s == '<' && ++(*s))
		*last = new_token(REDIR_IN, "<", *last);
	else if (**s == '>' && ++(*s))
		*last = new_token(REDIR_OUT, ">", *last);
	else if (**s == '|' && ++(*s))
		*last = new_token(PIPE, "|", *last);
	else if (**s == '(' && ++(*s))
		*last = new_token(LPARENT, "(", *last);
	else if (**s == ')' && ++(*s))
		*last = new_token(RPARENT, ")", *last);
	else if (**s == '&' && ++(*s))
		*last = new_token(INVALID, "&", *last);
	else if (**s == ';' && ++(*s))
		*last = new_token(INVALID, ";", *last);
}

/* Handle the words for lexer, default option. */
static void	handle_word(char **s, t_token **last)
{
	int	len;

	len = ft_next_len(*s, '\0');
	*last = new_token(WORD, ft_substr((const char *) *s, 0, len), *last);
	*s += len;
}

/* Generate a doubly linked list of tokens. */
t_token	*input_lexer(char *input)
{
	t_token	*start;
	t_token	*last;

	start = NULL;
	last = NULL;
	while (*input)
	{
		while (*input == ' ' || *input == '\t')
			++input;
		if (*input == '\0')
			break ;
		if (ft_isop(input))
			handle_op(&input, &last);
		else
			handle_word(&input, &last);
		if (!start && last)
			start = last;
	}
	return (start);
}
