/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 05:40:49 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/18 16:39:22 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMC_H
# define LIBMC_H

# include "libft.h"
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# define FT_PRINTF_SPECIFIERS	"%cdiuxXsp"
# define FT_PRINTF_FLAGS		"-0# +"
# define PRINTF_CONVERTERS		8
# define HEX_OFF_TO_LOWER		39
# define HEX_OFF_TO_UPPER		7
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE			4096
# endif

typedef struct s_stream
{
	int				fd;
	ssize_t			len;
	size_t			off;
	unsigned char	buff[BUFFER_SIZE];
}	t_stream;

/* 
** Flags bits:
** [0] left align(-); [1] zero padded(0); [2] alternate form(#);
** [3] prefix blank( ); [4] prefix sign(+);
*/
typedef struct s_fmt
{
	int		width;
	int		prec;
	int		specifier;
	int		flags;
	union
	{
		int				i;
		unsigned int	ui;
		void			*p;
	}		u_arg;
	char	*out;
}		t_fmt;

typedef char	*(*t_converter)(struct s_fmt *);

void		mc_putchar(char c);
char		**mc_split_blocks(const char *s, char c, const char *blockers);
char		*mc_itoa(int n);
char		*mc_uitoa(unsigned int n);
// mc_printf
int			mc_printf(const char *format, ...);
int			mc_dprintf(int fd, const char *format, ...);
int			mc_print(const char *str, int s, int e, int fd);
int			indexof(char c, char *str);
int			get_min_width(const char *fmt, int *i);
int			get_precision(const char *fmt, int *i);
char		*gen_padding(int c, int n);
char		*zero_padding(t_fmt *f, int len);
int			mc_printf_handle_flags(t_fmt *f, int fd);
int			mc_printf_char_flags(t_fmt *f, int fd);
int			mc_printf_format(t_fmt *f, va_list ap, int fd);
char		*mc_printf_int(t_fmt *fmt);
char		*mc_printf_uint(t_fmt *fmt);
char		*mc_printf_char(t_fmt *fmt);
char		*mc_printf_str(t_fmt *fmt);
char		*mc_printf_ptr(t_fmt *fmt);
char		*mc_printf_hex(t_fmt *fmt);
char		*mc_printf_uhex(t_fmt *fmt);

// get_delim
char		*get_delim(int fd, int delim);
void		*mc_memgrow(void *ptr, size_t old_size, size_t new_size);
void		*mc_memccpy(void *dest, const void *src, int c, size_t n);

#endif