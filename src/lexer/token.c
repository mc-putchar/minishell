/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 11:50:38 by dlu               #+#    #+#             */
/*   Updated: 2023/07/16 17:04:00 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Check if a character is a metacharacter. */
bool	ft_ismeta(char c)
{
	if (ft_strchr(" \t\n|&;()<>", c))
		return (true);
	else
		return (false);
}

/* Check if a the string is at an operator.
 * Handles '||', '&&', '<<', '>>', '<' '>', '|', '(', ')'. */
bool	ft_isop(char *s)
{
	if (ft_strncmp(s, "||", 2) == 0)
		return (true);
	if (ft_strncmp(s, "&&", 2) == 0)
		return (true);
	if (ft_strncmp(s, ">>", 2) == 0)
		return (true);
	if (ft_strncmp(s, "<<", 2) == 0)
		return (true);
	if (*s == '<' || *s == '>' || *s == '|' || *s == '(' || *s == ')')
		return (true);
	if (*s == '&' || *s == ';')
		return (true);
	return (false);
}

/* Generate a new token. */
t_token	*new_token(t_type type, char *value, t_token *prev)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->prev = prev;
	token->next = NULL;
	if (prev)
		prev->next = token;
	return (token);
}

/* Free the token list from the head. */
void	free_token(t_token *token)
{
	t_token	*temp;

	while (token)
	{
		temp = token;
		token = token->next;
		if (temp->type == WORD && temp->value)
			free(temp->value);
		free(temp);
	}
}
