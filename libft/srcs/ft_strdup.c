/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu<dlu@student.42berlin.de>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 04:56:55 by dlu               #+#    #+#             */
/*   Updated: 2023/05/23 11:39:23 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	len;

	len = ft_strlen(s1);
	dup = (char *) malloc((len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	while (*s1)
		*dup++ = *s1++;
	*dup = '\0';
	return (dup - len);
}
