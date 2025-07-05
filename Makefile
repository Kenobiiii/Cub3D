LIB = ar rcs
RM = rm -f

CC = clang
CFLAGS = -Wall -Werror -Wextra

USER = paromero
OBJ_DIR = objs
SRCS = src/main.c

OBJS = $(patsubst src/%.c, $(OBJ_DIR)/%.o, $(SRCS))

HEADERS = include/cub3d.h
NAME = cub3D

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDES = -I./$(LIBFT_DIR) -I/usr/include/readline
LIBS = -L./$(LIBFT_DIR) -lft -lreadline -lncurses

GREEN = \033[1;32m
RESET = \033[0m

all: $(LIBFT) $(OBJ_DIR) $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)Compiling objects...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)Executable created: $(NAME)$(RESET)"

$(OBJ_DIR)/%.o: src/%.c $(HEADERS) | $(OBJ_DIR)
	@echo "$(GREEN)Compiling $<...$(RESET)"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(GREEN)$< compiled!$(RESET)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@echo "$(GREEN)Building libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@echo "$(GREEN)Cleaning...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(RM) $(OBJS)
	@echo "$(GREEN)Clean complete.$(RESET)"

fclean: clean
	@echo "$(GREEN)Deleting $(NAME)...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -rf $(OBJ_DIR)
	@$(RM) $(NAME)
	@echo "$(GREEN)Deleted $(NAME)$(RESET)"

re: fclean all

.PHONY: all clean fclean re