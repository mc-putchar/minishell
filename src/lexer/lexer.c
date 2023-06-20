/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 10:28:59 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/20 16:21:32 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Check if the input line contains only white characters. */
static int	cmd_empty(const char *line)
{
	char *trimmed;

	trimmed = ft_strtrim(line, " \n\t\r\f\v");
	if (!trimmed[0])
		return (free(trimmed), TRUE);
	return (free(trimmed), FALSE);
}

/* Count the number of commands in an input line.*/
// i.e. bash (ls -la) -> runs the cmd; bash ((ls -la)) doesn't
// Also will be parsing errors: "| ls -la" (command start logical opeartor |, &&, ||)
// "syntax error near unexpected token" => check in validator
static int	cmd_count(const char *line)
{
	int	count;

	if (cmd_empty(line))
		return (0);
	count = 1;
	while (*line)
	{
		if (*line == '|' && *(line + 1) == ' ')
			++count;
		if (*line == '&' && *(line + 1) == '&' && ++line)
			++count;
		if (*line == '|' && *(line + 1) == '|' && ++line)
			++count;
		++line;
	}
	return (count);
}

/* Count the number of arguments from input, start at index i until the end of cmd. 
 * Based on |, ||, &&. */
//TODO: parentheses
//static int	arg_count(const char *line, int i)
//{
//}


/* */
// Free the line here?
// Return an array of commands, should never fail, any fail cases move to validator

// allocate cmd + 1 t_cmd, last one NULL?
// for each cmd, allocate arg_count + 1, NULL terminated, load the arguments and expand $
// parse all the redirections into the cmd as it reads
t_cmd	*input_lexer(char *line)
{
	const int	cmds = cmd_count((const char *) line);
	t_cmd		*ret;

	ret = (t_cmd *) malloc((cmds + 1) * sizeof (t_cmd));
	if (!ret)
		return (NULL);
	return (ret);
	//int	i;

	//tokens = ft_split_blocks(line, ' ', "\'\"");
	//if (!tokens)
	// while (tokens[i])
	// {
	// 	ft_printf("\r\nToken %d: %s\n\r", i, tokens[i]);
	// 	++i;
	// }
	/*
	cmd = parser(tokens);
	if (!cmd)
	while (cmd)
	{
		i = 0;
		while (cmd->args[i])
		{
			ft_printf("\r\nArg %d: %s\n\r", i, cmd->args[i]);
			++i;
		}
		ft_printf("\r\nType: %d\n\r", cmd->type);
		cmd = cmd->right;
	}*/
}

/*
#include <stdio.h>
int	main(void)
{
	const char *s1 = "abcd && acde && acd || ac | ads";
	const char *s2 = "			   ";
	const char *s3 = "abcd | abcd";
	const char *s4 = "abcd";
	printf("5: %d\n", cmd_count(s1));
	printf("0: %d\n", cmd_count(s2));
	printf("2: %d\n", cmd_count(s3));
	printf("1: %d\n", cmd_count(s4));
	return (0);
}*/
