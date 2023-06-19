/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:18:58 by dlu               #+#    #+#             */
/*   Updated: 2023/06/19 20:20:20 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Check string has right sequence for open and close parentheses. */
static int	valid_parentheses(const char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == '(')
			++count;
		if (*str == ')' && --count)
			if (count < 0)
				return (FALSE);
		++str;	
	}
	if (count)
		return (FALSE);
	return (TRUE);
}

/* Check string has the right sequence for single and double quotes. */
static int	valid_quotes(const char *str)
{
	char	top;
	int		open_d;
	int		open_s;
	
	top = '\0';
	open_d = 0;
	open_s = 0;
	while (*str)
	{
		if ((*str == '\'' || *str == '"') && open_d && open_s && top != *str)
			return (FALSE);
		else if (*str == '\'' && !open_s && ++open_s)
			top = *str;
		else if (*str == '\'')
			--open_s;
		else if (*str == '"' && !open_d && ++open_d)
			top = *str;
		else if (*str == '"')
			--open_d;
		++str;
	}
	if (open_d || open_s)
		return (FALSE);
	return (TRUE);
}

/* Check input string is valid before proceeding, print error otherwise. */
int	validate_input(const char *str)
{
	if (!valid_quotes(str))
		return (FALSE);
	if (!valid_parentheses(str))
		return (FALSE);
	return (TRUE);
}

/*
int	main(void)
{
	const char *str1 = "(a + b) * (c - d)";
	const char *str2 = "((a + b) * (c - d)";
	const char *str3 = "(a + b)) * (c - d)";
	printf("%d\n", valid_parentheses(str1));
	printf("%d\n", valid_parentheses(str2));
	printf("%d\n", valid_parentheses(str3));
	const char *str4 = "(a + b\"' * '\"(c - d)";
	const char *str5 = "((a + b)\" ' \" ' * (c - d)";
	const char *str6 = "(a + b)) \"\" \"\" '\"\"'* (c - d)";
	printf("%d\n", valid_quotes(str4));
	printf("%d\n", valid_quotes(str5));
	printf("%d\n", valid_quotes(str6));
	return (0);
}*/
