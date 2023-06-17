# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/17 11:04:09 by dlu               #+#    #+#              #
#    Updated: 2023/06/17 11:34:48 by dlu              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	minishell

SRCDIR	:=	src
_SRC	:=	main.c
SRC		:=	$(addprefix $(SRCDIR)/, $(_SRC))

OBJDIR	:=	obj
_OBJ	:=	$(_SRC:.c=.o)
OBJ		:=	$(addprefix $(OBJDIR)/, $(_OBJ))

INCDIR	:=	inc

LIBDIR	:=	libft
LIBNAME	:=	libft.a
LIBFT	:=	$(addprefix	$(LIBDIR)/, $(LIBNAME))

CC		:=	cc
RM		:=	/bin/rm -f
CFLAGS	:=	-Wall -Wextra -Werror -g
IFLAGS	:=	-I $(INCDIR) -I $(LIBDIR)
LFLAGS	:=	-L $(LIBDIR) -lft -lreadline

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $< $(IFLAGS)

$(LIBFT):
	@make -C $(LIBDIR) $(LIBNAME) >/dev/null

clean:
	@make -C $(LIBDIR) $@ >/dev/null
	$(RM) $(OBJ)
	
fclean: clean
	@make -C $(LIBDIR) $@ >/dev/null
	$(RM) $(NAME)

re: fclean all

var-%:
	@echo $($*)

.PHONY: all clean fclean re var-%
