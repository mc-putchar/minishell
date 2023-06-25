/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:18:58 by dlu               #+#    #+#             */
/*   Updated: 2023/06/25 17:50:16 by dlu              ###   ########.fr       */
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
		return (FALSE);
	return (TRUE);
}

/* Check string has the correct syntax, namely any cmd to start with | or &.
 * Some other invalid tokens: |* (anything other than | following antoher |)
 * &&* or ||* (anything other than space following || or &&). */
// This is working in progress. *** Parenthese suppport not yet implemented.
// TODO: cleanup the logic, maybe split into smaller functions.
static int	valid_syntax(const char *str)
{
	char	*s;
	int		has_char;
	int		i;
	
	s = ft_replace_quotes(str, '_');
	has_char = 0;
	i = -1;
	while (s[++i])
	{
		//ft_printf("%s, has_char: %d\n", &s[i], has_char);
		if (!has_char && (((s[i] == '|' && (s[i + 1] == '|'
			|| s[i + 1] == ' ')) || s[i] == '&')))
			return (free(s), FALSE);
		if (ft_isprint(s[i]) && s[i] != ' ' && s[i] != '|' && s[i] != '&')
			has_char = 1;
		else if ((s[i] == '|' && s[i] != '|') || (s[i] == '&' && s[i - 1] == '&'))
			has_char = 0;
	}
	return (free(s), TRUE);
}

/* Check input string is valid before proceeding, print error otherwise. */
int	input_validator(const char *str)
{
	if (!valid_quotes(str))
		return (FALSE);
	if (!valid_parentheses(str))
		return (FALSE);
	if (!valid_syntax(str))
		return (FALSE);
	return (TRUE);
}
/*
int	main(void)
{
	const char *str1 = "(a + b) * (c - d)";
	const char *str2 = "((a + b) * (c - d)";
	const char *str3 = "(a + b)) * (c - d)";
	const char *str4 = "(((a + b)) * (c - d))";
	printf("1: %d\n", valid_parentheses(str1));
	printf("0: %d\n", valid_parentheses(str2));
	printf("0: %d\n", valid_parentheses(str3));
	printf("1: %d\n", valid_parentheses(str4));
	const char *str5 = "\"'test''\"";
	const char *str6 = "'test''";
	const char *str7 = "'test' 'test\"\"\"' \"'test\"";
	printf("1: %d\n", valid_quotes(str5));
	printf("0: %d\n", valid_quotes(str6));
	printf("1: %d\n", valid_quotes(str7));
	const char *s1 = "    | \"'test''\"";
	const char *s2 = "'ls' '-la' || ab && ab || ac";
	const char *s3 = "    'test' | \"abc\" ";
	printf("0: %d\n", valid_syntax(s1));
	printf("1: %d\n", valid_syntax(s2));
	printf("1: %d\n", valid_syntax(s3));
	return (0);
}*/
