/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mc_printf_converters.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 22:19:16 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/18 06:31:59 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmc.h"

char	*mc_printf_int(t_fmt *fmt)
{
	char	*tmp;
	int		len;

	fmt->out = mc_itoa(fmt->u_arg.i);
	if (!fmt->prec && fmt->out[0] == '0')
		fmt->out[0] = 0;
	len = fmt->prec - ft_strlen(fmt->out);
	if (fmt->out[0] == '-')
		++len;
	if (len > 0)
	{
		tmp = zero_padding(fmt, len);
		free(fmt->out);
		fmt->out = tmp;
	}
	if (fmt->u_arg.i < 0)
		return (fmt->out);
	if (fmt->flags & (1 << 4))
		tmp = ft_strjoin("+", fmt->out);
	else if (fmt->flags & (1 << 3))
		tmp = ft_strjoin(" ", fmt->out);
	else
		return (fmt->out);
	return (free(fmt->out), fmt->out = tmp);
}

char	*mc_printf_uint(t_fmt *fmt)
{
	char	*str;
	char	*tmp;
	int		len;

	fmt->out = mc_uitoa(fmt->u_arg.ui);
	if (!fmt->prec && fmt->out[0] == '0')
		fmt->out[0] = 0;
	if (fmt->prec > (int)ft_strlen(fmt->out))
	{
		len = fmt->prec - ft_strlen(fmt->out);
		str = malloc(len + 1);
		str[len] = 0;
		while (len--)
			str[len] = '0';
		tmp = ft_strjoin(str, fmt->out);
		free(fmt->out);
		fmt->out = tmp;
		return (free(str), fmt->out);
	}
	return (fmt->out);
}

char	*mc_printf_char(t_fmt *fmt)
{
	unsigned char	c;

	c = (unsigned char)fmt->u_arg.i;
	fmt->out = malloc(2);
	if (!fmt->out)
		return (NULL);
	fmt->out[0] = c;
	fmt->out[1] = 0;
	return (fmt->out);
}

char	*mc_printf_str(t_fmt *fmt)
{
	if (!fmt->u_arg.p)
	{
		if (fmt->prec)
			return (fmt->out = ft_strdup("(null)"));
		else
			return (fmt->out = ft_strdup(""));
	}
	fmt->out = ft_strdup((const char *)fmt->u_arg.p);
	if (!fmt->out)
		return (NULL);
	if (fmt->prec != -1 && fmt->prec < (int)ft_strlen(fmt->out))
		fmt->out[fmt->prec] = 0;
	return (fmt->out);
}
