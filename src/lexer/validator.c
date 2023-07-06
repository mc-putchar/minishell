/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:18:58 by dlu               #+#    #+#             */
/*   Updated: 2023/07/06 06:37:14 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Check string has right sequence for open and close parentheses. */
static bool	valid_parentheses(const char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == '(')
			++count;
		if (*str == ')' && --count)
			if (count < 0)
				return (false);
		++str;
	}
	if (count)
		return (false);
	return (true);
}

/* Check string has the right sequence for single and double quotes. */
static bool	valid_quotes(const char *str)
{
	int	quote_s;
	int	quote_d;

	quote_d = 0;
	quote_s = 0;
	while (*str)
	{
		if (*str == '\'' && quote_d % 2 == 0)
			++quote_s;
		if (*str == '"' && quote_s % 2 == 0)
			++quote_d;
		++str;
	}
	if (quote_d % 2 || quote_s % 2)
		return (false);
	return (true);
}

/* Check input string is valid before proceeding, print error otherwise. */
bool	input_validator(const char *str)
{
	char	*trimmed;

	trimmed = ft_strtrim(str, " \t\v\n\f\r");
	if (!trimmed || !trimmed[0])
		return (free(trimmed), false);
	free(trimmed);
	if (!valid_quotes(str))
		return (ft_perror("unmatched quotes"), false);
	if (!valid_parentheses(str))
		return (ft_perror("unmatched parentheses"), false);
	return (true);
}
