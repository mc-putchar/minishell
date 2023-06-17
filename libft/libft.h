/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu<dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 22:28:32 by dlu               #+#    #+#             */
/*   Updated: 2023/06/08 09:34:24 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <limits.h>
# include <stdarg.h>
# include <unistd.h>
# include <sys/types.h>

typedef unsigned char		t_uc;
typedef unsigned int		t_ui;
typedef unsigned long long	t_ull;
typedef long long			t_ll;

# define DEC		"0123456789"
# define HEXU		"0123456789ABCDEF"
# define HEXL		"0123456789abcdef"
# define NULL_STR	"(null)"
# define NULL_PTR	"(nil)"

/* Basic functions. */

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_atoi(const char *str);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_itoa(int n);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	**ft_split(char const *s, char c);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_calloc(size_t count, size_t size);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

/* Linked list. */

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_lstsize(t_list *lst);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/* Printf. */

typedef struct s_format
{
	t_ll	nbr;
	char	type;
	char	padding;
	char	*num;
	int		hash;
	int		minus;
	int		plus;
	int		space;
	int		dot;
	int		zero;
	int		width;
	int		precision;
	int		base;
	int		signed_nbr;
}	t_format;

int		ft_printf(const char *s, ...);
int		ft_strlenf(char *s, t_format format);
int		print_padding(char c, int len);
int		print_str(char *s, int *count, t_format format);
void	print_char(char c, int *count, t_format format);
void	print_ptr(void *p, int *count, t_format format);
void	print_arg(va_list *args, int *count, t_format format);
void	print_nbr(t_ll n, const char *base, int *count, t_format format);
void	parse_nbr(t_ll n, const char *base, t_format *format);
void	parse_format(char **s, va_list *args, t_format *format);

/* Get next line. */

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

char	*get_next_line(int fd);
int		nl_index(char *prev, int end);
int		append_buffer(char **prev, char *buffer, ssize_t n);

#endif
