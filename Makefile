# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/08 19:09:15 by mcutura           #+#    #+#              #
#    Updated: 2023/06/19 00:53:01 by dlu              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	minishell

#--- DIRECTORIES ---
SRCDIR		:=	src
INCDIR		:=	inc
OBJDIR		:=	obj
SUBDIR		:=	director lexer parser xecutor
LIBFTDIR	:=	libft
LIBMCDIR	:=	libmc

#--- LIBRARIES ---
LIBFT	:= $(LIBFTDIR)/libft.a
LIBMC	:= $(LIBMCDIR)/libmc.a

#--- SOURCES ---

SRC		:=	main.c \
			director/build_prompt.c director/director.c director/init_shell.c \
			director/read_line.c director/setup_terminal.c \
			lexer/lexer.c \
			parser/parser.c \
			xecutor/builtin.c xecutor/redirect.c xecutor/xecutor.c
SRCS	:=	$(addprefix $(SRCDIR)/, $(SRC))

#--- OBJECTS ---
OBJS	:=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))

#--- HEADERS ---
HEADER	:=	minishell.h cmd_table.h control_sequences.h format_output.h
HEADERS	:=	$(addprefix $(INCDIR)/, $(HEADER))
LIBFTHEADER	:=	$(addprefix $(LIBFTDIR)/, libft.h)
LIBMCHEADER	:=	$(addprefix $(LIBMCDIR)/, libmc.h)

#--- FLAGS ---
CFLAGS	:=	-Wall -Wextra -Werror -I$(INCDIR) -I$(LIBMCDIR) -I$(LIBFTDIR)
LDFLAGS	:=	-L$(LIBMCDIR) -L$(LIBFTDIR)
LDLIBS	:=	-lmc -lft

#--- CMDS ---
CC		:=	cc
RM		:=	/bin/rm -rf
MUTE	:=	>/dev/null

#--- RULES ---
.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(HEADERS) $(LIBMC) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS) $(LDLIBS)

$(LIBFT): $(LIBFTHEADER)
	@$(MAKE) -C $(LIBFTDIR) $(MUTE)

$(LIBMC): $(LIBMCHEADER)
	@$(MAKE) -C $(LIBMCDIR) $(MUTE)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR) && cd $(OBJDIR) && mkdir -p $(SUBDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	@$(MAKE) -C $(LIBFTDIR) $@ $(MUTE)
	@$(MAKE) -C $(LIBMCDIR) $@ $(MUTE)

fclean: clean
	@$(MAKE) -C $(LIBFTDIR) $@ $(MUTE)
	@$(MAKE) -C $(LIBMCDIR) $@ $(MUTE)
	$(RM) $(OBJDIR)
	$(RM) $(NAME)

re: fclean all
