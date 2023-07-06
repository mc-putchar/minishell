/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 05:01:45 by dlu               #+#    #+#             */
/*   Updated: 2023/07/06 06:40:08 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Check if a str matches the format (*). */
static bool	wildcard_match(char *str, char *format)
{
	while (*format)
	{
		if (*format == (char) WC_CHAR)
		{
			while (*format == (char) WC_CHAR)
				++format;
			if (!*format)
				return (true);
			while (*str)
			{
				if (wildcard_match(str, format))
					return (true);
				++str;
			}
		}
		else if (*format == *str)
		{
			++format;
			++str;
		}
		else
			return (false);
	}
	return (*format == *str);
}

/* Convert * back. */
static void	reformat(char *str)
{
	while (*str)
	{
		if (*str == (char) WC_CHAR)
			*str = '*';
		++str;
	}
}

/* Wildcard expansion, return new index. */
int	wildcard_expansion(char **args, char *format, int i)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*temp;
	bool			found;

	temp = format;
	dir = opendir(".");
	if (!dir)
		return (ft_perror("opendir"), i);
	entry = readdir(dir);
	found = false;
	while (entry)
	{
		if (entry->d_name[0] != '.' && wildcard_match(entry->d_name, format)
			&& i < MAX_ARG_E)
		{
			args[i++] = ft_strdup(entry->d_name);
			found = true;
		}
		entry = readdir(dir);
	}
	if (!found)
		return (closedir(dir), reformat(args[i]), i + 1);
	return (closedir(dir), free(temp), i);
}
