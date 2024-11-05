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
			$(SRC_DIR)/cost.c \
			$(SRC_DIR)/cost_reduction.c \
			$(SRC_DIR)/input_handling/input_handler.c \
			$(SRC_DIR)/input_handling/input_util.c

ifeq ($(DEBUG), debug)
	SRC		+= \
			$(SRC_DIR)/debug/dbg_pushes.c \
			$(SRC_DIR)/debug/dbg_rev_rotations.c \
			$(SRC_DIR)/debug/dbg_rotations.c \
			$(SRC_DIR)/debug/dbg_swaps.c \
			$(SRC_DIR)/debug/sort.c

else ifeq ($(DEBUG), test)
	SRC		+= \
			$(SRC_DIR)/test/dbg_pushes.c \
			$(SRC_DIR)/test/dbg_rev_rotations.c \
			$(SRC_DIR)/test/dbg_rotations.c \
			$(SRC_DIR)/test/dbg_swaps.c \
			$(SRC_DIR)/test/sort.c

else
	SRC		+= \
			$(SRC_DIR)/ops/pushes.c \
			$(SRC_DIR)/ops/rev_rotations.c \
			$(SRC_DIR)/ops/rotations.c \
			$(SRC_DIR)/ops/swaps.c \
			$(SRC_DIR)/sort.c
endif

TITLE		?= test
NUM_RUNS	?= 1000

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
			rm -f $(SRC_DIR)/test/*.o
			$(MAKE) --directory $(PRINTF_DIR) clean
			$(MAKE) --directory $(LIBFT_DIR) clean


fclean:		clean
			rm -f $(NAME)
			rm -f $(LIBFT)
			rm -f $(PRINTF)

test:
			@mv push_swap.out $(TITLE).out
			@./test/run.py ./$(TITLE).out --num_runs=$(NUM_RUNS) --output=output.png --threads=12
			@mv output.png $(NUM_RUNS)-$(TITLE)-$$(date +%H%M%S).png
			@echo "Done"

re:			fclean all

.PHONY:		re all clean fclean bonus test