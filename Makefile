# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/08 19:09:15 by mcutura           #+#    #+#              #
#    Updated: 2023/06/18 22:35:43 by mcutura          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell
#--- DIRECTORIES ---
SRCDIR :=		src
DIRECTORDIR :=	director
LEXERDIR :=		lexer
PARSERDIR :=	parser
XECUTORDIR :=	xecutor
INCDIR :=		inc
OBJDIR :=		obj
LIBFTDIR :=		libft
LIBMCDIR :=		libmc
#--- LIBRARIES ---
LIBFT := $(LIBFTDIR)/libft.a
LIBMC := $(LIBMCDIR)/libmc.a
#--- SOURCES ---
SRCDIRECTOR := $(addprefix $(DIRECTORDIR)/, director.c build_prompt.c \
	setup_terminal.c init_shell.c read_line.c)
SRCLEXER := $(addprefix $(LEXERDIR)/, lexer.c)
SRCPARSER := $(addprefix $(PARSERDIR)/, parser.c)
SRCXECUTOR := $(addprefix $(XECUTORDIR)/, xecutor.c redirect.c builtin.c)
SRCS := $(addprefix $(SRCDIR)/, main.c $(SRCDIRECTOR) $(SRCLEXER) \
	$(SRCPARSER) $(SRCXECUTOR))
#--- OBJECTS ---
OBJS := $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))
#OBJS := $(patsubst %.c, $(OBJDIR)/%.o, $(notdir $(SRCS)))
#--- HEADERS ---
HEADERS := $(addprefix $(INCDIR)/, minishell.h cmd_table.h \
	control_sequences.h format_output.h)
LIBFTHEADER := $(addprefix $(LIBFTDIR)/, libft.h)
LIBMCHEADER := $(addprefix $(LIBMCDIR)/, libmc.h)
#--- FLAGS ---
CFLAGS := -Wall -Wextra -Werror -I$(INCDIR) -I$(LIBMCDIR) -I$(LIBFTDIR)
LDFLAGS := -L$(LIBMCDIR) -L$(LIBFTDIR)
LDLIBS := -lmc -lft

#--- RULES ---
.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(HEADERS) $(LIBMC) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS) $(LDLIBS)

$(LIBFT): $(LIBFTHEADER)
	$(MAKE) -C $(LIBFTDIR)

$(LIBMC): $(LIBMCHEADER)
	$(MAKE) -C $(LIBMCDIR)

$(OBJS): $(SRCS) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $(SRCS)
	mv *.o $(OBJDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	$(RM) $(OBJS)
	$(RM) -r $(OBJDIR)
	$(MAKE) -C $(LIBFTDIR) clean
	$(MAKE) -C $(LIBMCDIR) clean

fclean: clean
	$(MAKE) -C $(LIBFTDIR) fclean
	$(MAKE) -C $(LIBMCDIR) fclean
	$(RM) $(NAME)

re: fclean all
