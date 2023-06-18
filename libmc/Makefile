# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/18 05:41:57 by mcutura           #+#    #+#              #
#    Updated: 2023/06/18 12:14:58 by mcutura          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libmc.a
#--- DIRECTORIES ---
SRCDIR :=		src
OBJDIR :=		obj
LIBFTDIR :=		../libft
#--- SOURCES ---
SRCS := $(addprefix $(SRCDIR)/, get_delim.c  mc_itoa.c  mc_memccpy.c \
mc_memgrow.c mc_printf.c mc_printf_converters.c mc_printf_converters_hex.c \
mc_printf_handle_flags.c mc_printf_utils.c mc_split_blocks.c mc_putchar.c)

#--- LIBRARIES ---
LIBFT := $(LIBFTDIR)/libft.a

#--- HEADERS ---
HEADERS := libmc.h
LIBFTHEADER := $(LIBFTDIR)/libft.h

#--- OBJECTS ---
OBJS := $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))

#--- FLAGS ---
CFLAGS := -Wall -Wextra -Werror -I. -I$(LIBFTDIR)
ARFLAGS := rcs

#--- RULES ---
.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(HEADERS) $(LIBFT) $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIBFT): $(LIBFTHEADER)
	$(MAKE) -C $(LIBFTDIR)

clean:
	$(RM) $(OBJS)
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all
