/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_blocks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:56:47 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/19 13:50:19 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_next_block(const char *s, char c, int i, const char *blockers)
{
	int		start;
	int		end;
	int		in_block;

	start = 0;
	end = 0;
	in_block = 0;
	while (s[end])
	{
		if (s[end] == c && !in_block)
		{
			if (!i--)
				break ;
			start = end + 1;
		}
		else if (ft_strchr(blockers, s[end]))
			in_block = !in_block;
		++end;
	}
	if (!end)
		return (NULL);
	if (ft_strchr(blockers, s[start]) && ++start && --end)
		;
	return (ft_substr(s, start, end - start));
}

static int	ft_count_blocks(const char *s, char c, const char *blockers)
{
	int	count;
	int	i;
	int	in_block;

	count = 0;
	i = 0;
	in_block = 0;
	while (s[i])
	{
		if (s[i] == c && !in_block)
			count++;
		else if (ft_strchr(blockers, s[i]))
			in_block = !in_block;
		i++;
	}
	if (i > 0 && s[i - 1] != c)
		count++;
	return (count);
}

char	**ft_split_blocks(const char *s, char c, const char *blockers)
{
	char	**spl;
	int		count;
	int		i;

	count = ft_count_blocks(s, c, blockers);
	spl = malloc(sizeof(char *) * (count + 1));
	if (!spl)
		return (NULL);
	i = 0;
	while (i < count)
	{
		spl[i] = get_next_block(s, c, i, blockers);
		if (!spl[i++])
		{
			while (i-- - 1)
				free(spl[i]);
			free(spl);
			return (NULL);
		}
	}
	spl[i] = NULL;
	return (spl);
}

/*
#include <stdio.h>
int main(void)
{
	char *s = "hello world sed -e 's/abc/def/g' -e 's/123/456/g'";
	char **spl = ft_split_blocks(s, ' ', "'\"");
	if (!spl)
		return (1);
	int i = 0;
	while (spl[i])
	{
		printf("%s\n", spl[i++]);
	}
	while (i--)
	{
		free(spl[i]);
	}
	free(spl);
	return (0);
}
*/
