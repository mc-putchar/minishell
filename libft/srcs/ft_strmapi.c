/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu<dlu@student.42berlin.de>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 00:26:30 by dlu               #+#    #+#             */
/*   Updated: 2023/05/23 11:50:05 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ret;
	int		i;

	i = -1;
	if (!s)
		return (NULL);
	ret = (char *) malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	while (s[++i])
		ret[i] = f((unsigned int) i, s[i]);
	ret[i] = '\0';
	return (ret);
}
