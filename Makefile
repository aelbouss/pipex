NAME = pipex
CC = cc
CFLAGS = -Wall -Werror -Wextra
SRCS = pipex.c pipex_utils.c pipex_utils2.c split.c
BONUS_SRCS = pipex_bonus.c pipex_bonus_helpers.c pipex_bonus_helpers2.c pipex_bonus_helpers3.c split.c
RM = rm -rf
SRCS_OBJ = $(SRCS:.c=.o)
BONUS_OBJ = $(BONUS_SRCS:.c=.o)
HEADER = pipex.h
HEADER_BONUS = pipex_bonus.h

ifeq ($(MAKECMDGOALS),bonus)
OBJ = $(BONUS_OBJ)
else
OBJ = $(SRCS_OBJ)
endif

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

all: $(NAME)

bonus: $(NAME)

%.o: %.c $(HEADER) $(HEADER_BONUS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(SRCS_OBJ) $(BONUS_OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

bonus_re: fclean bonus

.PHONY: fclean clean re all bonus bonus_re
