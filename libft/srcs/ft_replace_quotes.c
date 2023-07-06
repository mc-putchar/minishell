/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:55:49 by dlu               #+#    #+#             */
/*   Updated: 2023/07/06 04:35:08 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Replace anything within quotes with another char. */
char	*ft_replace_quotes(const char *str, char replace)
{
	char	*ret;
	char	quote;
	int		i;

	ret = (char *) ft_calloc(sizeof (char), ft_strlen(str) + 1);
	if (!ret)
		return (NULL);
	i = 0;
	quote = 0;
	while (*str)
	{
		if (!quote && (*str == '\'' || *str == '"'))
		{
			quote = *str;
			ret[i++] = replace;
		}
		else if (quote == *str)
			quote = 0;
		else if (!quote)
			ret[i++] = *str;
		++str;
	}
	ret[i] = '\0';
	return (ret);
}

/*
int	main(void)
{
	const char	*s1 = "abc \"abcabc'\" 'abcabc""|'";
	ft_printf("%s\n", replace_quotes(s1, '_'));
	return (0);
}*/
