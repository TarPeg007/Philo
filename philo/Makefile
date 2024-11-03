# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/18 18:26:38 by sfellahi          #+#    #+#              #
#    Updated: 2024/11/03 14:55:34 by sfellahi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror #-g   -fsanitize=thread

SRCS = philo.c libft_function.c mutex.c simulation.c utils.c
OBJS = $(SRCS:.c=.o)

NAME = philo

GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RESET = \033[0m

# Fun animation frames
ANIM_FRAMES = "\t(~_~)\n" "\t(o_O)\n" "\t(^_^)\n" "\t(x_x)\n" "\t(O_O)\n" "\t(^_^)\n" "\t(z.Z)\n"

# Default rule
all: $(NAME)

# Build the executable
$(NAME): $(OBJS)
	@echo "$(GREEN)Compiling...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(BLUE)Philosophers are deep in thought...$(RESET)"
	@for frame in $(ANIM_FRAMES); do \
		printf "\r$$frame"; \
		sleep 0.52; \
	done
	@echo "$(GREEN)\nBuild complete: $(NAME) created!$(RESET)"
	@echo "$(BLUE)Created by TarPeg007$(RESET)"

# Compile .o files
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	@echo "$(RED)Cleaning up object files...$(RESET)"
	@rm -f $(OBJS)

# Full clean, including executable
fclean: clean
	@echo "$(RED)Full clean: removing $(NAME)...$(RESET)"
	@rm -f $(NAME)

# Recompile
re: fclean all

.PHONY: all clean fclean re
