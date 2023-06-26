/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarrcpy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:20:53 by dlu               #+#    #+#             */
/*   Updated: 2023/06/08 16:29:02 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strarrcpy(char **arr)
{
	char	**ret;
	int		i;

	ret = (char **) malloc(sizeof(char *) * (ft_strarrlen(arr) + 1));
	if (!ret)
		return (NULL);
	i = -1;
	while (arr[++i])
	{
		ret[i] = ft_strdup(arr[i]);
		if (!ret[i])
		{
			while (--i >= 0)
				free(ret[i]);
			return (free(ret), NULL);
		}
	}
	return (ret);
}
