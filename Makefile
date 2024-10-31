NAME		= push_swap.out

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3 -O0

SRC_DIR		= ./src
LIB_DIR		= ./lib

LIBFT_DIR	:= $(abspath $(LIB_DIR)/libft)
LIBFT		:= $(LIBFT_DIR)/libft.a

PRINTF_DIR	:= $(abspath $(LIB_DIR)/ftprintf)
PRINTF		:= $(PRINTF_DIR)/libftprintf.a

HEADER		= $(SRC_DIR)/push_swap.h
MAIN		= $(SRC_DIR)/main.c

SRC			= \
			$(SRC_DIR)/generics.c \
			$(SRC_DIR)/debug/printable.c \
			$(SRC_DIR)/struct_data.c \
			$(SRC_DIR)/struct_stack.c \
			$(SRC_DIR)/struct_opcst.c \
			$(SRC_DIR)/cost.c

ifeq ($(DEBUG), debug)
	SRC		+= \
			$(SRC_DIR)/debug/dbg_pushes.c \
			$(SRC_DIR)/debug/dbg_rev_rotations.c \
			$(SRC_DIR)/debug/dbg_rotations.c \
			$(SRC_DIR)/debug/dbg_swaps.c \
			$(SRC_DIR)/debug/sort.c
else
	SRC		+= \
			$(SRC_DIR)/ops/pushes.c \
			$(SRC_DIR)/ops/rev_rotations.c \
			$(SRC_DIR)/ops/rotations.c \
			$(SRC_DIR)/ops/swaps.c \
			$(SRC_DIR)/sort.c
endif

OBJ			= $(SRC:.c=.o)

# Targets

all:		$(NAME)


$(LIBFT):
			$(MAKE) --directory $(LIBFT_DIR)


$(PRINTF):
			$(MAKE) --directory $(PRINTF_DIR)


$(NAME):	$(MAIN) $(HEADER) $(PRINTF) $(LIBFT) $(OBJ)
			$(CC) $(CFLAGS) -o $(NAME) $(MAIN) $(OBJ) $(PRINTF) $(LIBFT)


.c.o:
		$(CC) $(CFLAGS) -o $@ -c $<


clean:
			rm -f $(OBJ)
			rm -f $(SRC_DIR)/debug/*.o
			$(MAKE) --directory $(PRINTF_DIR) clean
			$(MAKE) --directory $(LIBFT_DIR) clean


fclean:		clean
			rm -f $(NAME)
			rm -f $(LIBFT)
			rm -f $(PRINTF)


re:			fclean all


.PHONY:		re all clean fclean bonus