NAME = cub3d

CC = gcc
CFLAGS = -Wall -Wextra -Werror
COMPILE = $(CC) $(CFLAGS)
LIBFT = ./libft
LIB = $(LIBFT)/libft.a

INCLUDES =	-I$(LIBFT)\
			-Iminilibx\
			-Iincludes



LIBDIRS =	-Lminilibx\
			-L$(LIBFT)

LIBS =	-lft\
		-lmlx

FRAMEWORKS =	-framework OpenGL\
				-framework AppKit

SDIR = ./src

SRCS =	main.c\
		draw.c\
		utils.c\
		raycast.c\
		controls.c\
		movement.c

ODIR = ./obj
OBJS = $(patsubst %,$(ODIR)/%,$(SRCS:.c=.o))

$(ODIR)/%.o : $(SDIR)/%.c
	@mkdir -p obj
	@echo "Creating object : $@"
	@$(COMPILE) $(INCLUDES) -c -o $@ $<

all: libft | $(NAME)

$(NAME): $(LIB) $(OBJS)
	@echo "Creating executable $(NAME)"
	@$(COMPILE) $(OBJS) $(LIBDIRS) $(LIBS) $(FRAMEWORKS) -o $(NAME)

run: $(NAME)
	@./$<
	@echo "Worked just fine"

clean:
	@echo "Removing object files $(NAME)"
	@rm -rf $(OBJS) $(ODIR)
	@$(MAKE) clean -C $(LIBFT)

fclean: clean
	@echo "Removing executable file $(NAME)"
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT)

libft:
	@$(MAKE) -C $(LIBFT)

re: fclean | all

.PHONY: all clean fclean libft run re
