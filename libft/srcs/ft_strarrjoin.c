/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarrjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 04:24:47 by dlu               #+#    #+#             */
/*   Updated: 2023/07/06 04:34:45 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strarrjoin(char **arr1, char **arr2)
{
	const int	len = ft_strarrlen(arr1) + ft_strarrlen(arr2);
	char		**ret;
	int			i;
	int			j;

	if (!arr1 || !arr2)
		return (NULL);
	ret = (char **) malloc((len + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	i = -1;
	while (arr1[++i])
		ret[i] = arr1[i];
	j = -1;
	while (arr2[++j])
		ret[i++] = arr2[j];
	ret[i] = NULL;
	return (ret);
}
