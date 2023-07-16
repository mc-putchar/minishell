# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/08 19:09:15 by mcutura           #+#    #+#              #
#    Updated: 2023/07/15 14:51:36 by mcutura          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	minishell

#--- DIRECTORIES ---
SRCDIR	:=	src
INCDIR	:=	inc
OBJDIR	:=	obj
SUBDIR	:=	director lexer parser xecutor builtin debug reader
LIBDIR	:=	libft

#--- LIBRARIES ---
LIBFT	:=	$(LIBDIR)/libft.a

#--- SOURCES ---

SRC		:=	main.c \
			director/build_prompt.c director/director.c director/read_line.c \
			director/setup_terminal.c director/history.c \
			director/history_ctrl.c director/parse_execute.c \
			director/run_script.c \
			lexer/token.c lexer/lexer.c lexer/validator.c \
			parser/ast_basic.c parser/ast_block.c parser/ast_command.c \
			parser/ast_redir.c \
			builtin/builtin.c builtin/builtin_echo.c builtin/builtin_dir.c \
			builtin/builtin_environ.c builtin/builtin_exit.c builtin/env.c \
			builtin/builtin_help.c \
			xecutor/xecutor.c xecutor/cmd_validator.c xecutor/cmd_expansion.c \
			xecutor/pipex.c xecutor/redirect.c xecutor/wildcard.c \
			xecutor/here_doc.c xecutor/signal.c xecutor/logic_op.c \
			debug/ast_display.c debug/tokens_print.c \
			reader/line_moves.c reader/jmp_moves.c reader/line_clear.c \
			reader/screen_clear.c reader/delete.c reader/mission_ctrl.c
SRCS	:=	$(addprefix $(SRCDIR)/, $(SRC))

#--- OBJECTS ---
OBJS	:=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))

#--- HEADERS ---
HEADER	:=	minishell.h control_sequences.h format_output.h lexer.h
HEADERS	:=	$(addprefix $(INCDIR)/, $(HEADER))
LIBFTH	:=	$(addprefix $(LIBDIR)/, libft.h)

#--- FLAGS ---
CFLAGS	:=	-Wall -Wextra -Werror -I$(INCDIR) -I$(LIBDIR)
debug: CFLAGS += -ggdb3
LDLIBS	:=	-L$(LIBDIR) -lft

#--- CMDS ---
CC		:=	cc
RM		:=	/bin/rm -rf
MUTE	:=	>/dev/null

#--- RULES ---
.PHONY: all clean debug fclean re

all: $(NAME)

$(NAME): $(HEADERS) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDLIBS)

$(LIBFT): $(LIBFTH)
	$(MAKE) -C $(LIBDIR) all $(MUTE)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR) && cd $(OBJDIR) && mkdir -p $(SUBDIR)
	$(CC) $(CFLAGS) -c $< -o $@

debug: $(NAME)

clean:
	$(RM) $(OBJS)
	@$(MAKE) -C $(LIBDIR) $@ $(MUTE)

fclean: clean
	@$(MAKE) -C $(LIBDIR) $@ $(MUTE)
	$(RM) $(OBJDIR)
	$(RM) $(NAME)

re: fclean all
