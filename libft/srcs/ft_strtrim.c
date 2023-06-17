/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu<dlu@student.42berlin.de>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:13:39 by dlu               #+#    #+#             */
/*   Updated: 2023/05/23 11:50:40 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && ft_strchr(set, s1[start]))
		++start;
	while (s1[end] && ft_strchr(set, s1[end]) && end > 0)
		--end;
	if (start > end + 1)
		return (ft_strdup(""));
	return (ft_substr(s1, start, end - start + 1));
}
