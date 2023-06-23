/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 11:50:38 by dlu               #+#    #+#             */
/*   Updated: 2023/06/23 13:05:20 by dlu              ###   ########.fr       */
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
