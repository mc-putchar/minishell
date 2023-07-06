# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/08 19:09:15 by mcutura           #+#    #+#              #
#    Updated: 2023/07/06 08:06:44 by dlu              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	minishell

#--- DIRECTORIES ---
SRCDIR	:=	src
INCDIR	:=	inc
OBJDIR	:=	obj
SUBDIR	:=	director lexer parser xecutor builtin debug
LIBDIR	:=	libft

#--- LIBRARIES ---
LIBFT	:=	$(LIBDIR)/libft.a

#--- SOURCES ---

SRC		:=	main.c \
			director/build_prompt.c director/director.c director/init_shell.c \
			director/read_line.c director/setup_terminal.c director/history.c \
			director/history_ctrl.c director/parse_execute.c \
			lexer/token.c lexer/lexer.c lexer/validator.c \
			parser/ast_basic.c parser/ast_block.c parser/ast_command.c \
			parser/ast_redir.c \
			builtin/builtin.c builtin/builtin_echo.c builtin/builtin_dir.c \
			builtin/builtin_environ.c builtin/builtin_exit.c \
			xecutor/xecutor.c xecutor/cmd_validator.c xecutor/cmd_expansion.c \
			xecutor/pipex.c xecutor/redirect.c xecutor/wildcard.c \
			debug/ast_display.c debug/tokens_print.c
SRCS	:=	$(addprefix $(SRCDIR)/, $(SRC))

#--- OBJECTS ---
OBJS	:=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))

#--- HEADERS ---
HEADER	:=	minishell.h control_sequences.h format_output.h lexer.h
HEADERS	:=	$(addprefix $(INCDIR)/, $(HEADER))
LIBFTH	:=	$(addprefix $(LIBDIR)/, libft.h)

#--- FLAGS ---
CFLAGS	:=	-Wall -Wextra -Werror -g -I$(INCDIR) -I$(LIBDIR)
LDLIBS	:=	-L$(LIBDIR) -lft

#--- CMDS ---
CC		:=	cc
RM		:=	/bin/rm -rf
MUTE	:=	>/dev/null

#--- RULES ---
.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(HEADERS) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDLIBS)

$(LIBFT): $(LIBFTH)
	$(MAKE) -C $(LIBDIR) all $(MUTE)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR) && cd $(OBJDIR) && mkdir -p $(SUBDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	@$(MAKE) -C $(LIBDIR) $@ $(MUTE)

fclean: clean
	@$(MAKE) -C $(LIBDIR) $@ $(MUTE)
	$(RM) $(OBJDIR)
	$(RM) $(NAME)

re: fclean all
