# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: ajanse <ajanse@student.42.fr>                +#+                      #
#                                                    +#+                       #
#    Created: 2021/12/03 18:42:14 by ajanse        #+#    #+#                  #
#    Updated: 2022/03/09 16:23:14 by ajanse        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
COMPILE = $(CC) $(CFLAGS)
RM = rm -rf

SRCS =	ft_isalpha.c\
		ft_isdigit.c\
		ft_isalnum.c\
		ft_isascii.c\
		ft_isprint.c\
		ft_strlen.c\
		ft_memset.c\
		ft_bzero.c\
		ft_memcpy.c\
		ft_memmove.c\
		ft_strlcpy.c\
		ft_strlcat.c\
		ft_toupper.c\
		ft_tolower.c\
		ft_strchr.c\
		ft_strrchr.c\
		ft_strncmp.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_strnstr.c\
		ft_atoi.c\
		ft_calloc.c\
		ft_strdup.c\
		ft_strjoin.c\
		ft_substr.c\
		ft_strtrim.c\
		ft_split.c\
		ft_itoa.c\
		ft_strmapi.c\
		ft_striteri.c\
		ft_putchar_fd.c\
		ft_putstr_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		get_next_line.c\
		get_next_line_utils.c\
		ft_ptrarlen.c\
		free_ptrarray.c

ODIR = obj
_OBJS = $(SRCS:.c=.o)
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

$(ODIR)/%.o : %.c libft.h
	@mkdir -p obj
	@$(COMPILE) -c -o $@ $<

all: $(NAME)

$(NAME): $(OBJS)
	@ar -rcs $@ $^
	@echo "Creating libft.a"

clean:
	@$(RM) $(OBJS) $(ODIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
