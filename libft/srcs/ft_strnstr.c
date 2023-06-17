/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu<dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 09:13:21 by dlu               #+#    #+#             */
/*   Updated: 2023/05/18 17:07:36 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!*needle)
		return ((char *) haystack);
	while (i < len && haystack[i])
	{
		while ((i + j) < len && haystack[i + j] == needle[j]
			&& haystack[i + j])
			++j;
		if (!needle[j])
			return ((char *) haystack + i);
		j = 0;
		++i;
	}
	return (NULL);
}
