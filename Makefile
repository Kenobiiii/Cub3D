LIB = ar rcs
RM = rm -f

CC = clang
CFLAGS = -Wall -Werror -Wextra

USER = paromero
OBJ_DIR = objs

# MLX42 Configuration
MLX42_DIR = MLX
MLX42_BUILD = $(MLX42_DIR)/build
MLX42_LIB = $(MLX42_BUILD)/libmlx42.a
MLX42_FLAGS = -ldl -lglfw -pthread -lm
SRCS = src/main.c \
       src/parsing/parse.c \
       src/parsing/config_elements.c \
       src/parsing/config_utils.c \
       src/parsing/config_helpers.c \
       src/parsing/color_utils.c \
       src/parsing/map_reader.c \
       src/parsing/map_validator.c \
       src/parsing/player_validator.c \
       src/parsing/wall_validator.c \
       src/parsing/wall_utils.c \
       src/parsing/wall_helpers.c \
       src/parsing/memory_utils.c \
       src/engine/mlx_init.c \
       src/engine/texture_init.c \
       src/engine/render_basic.c \
       src/engine/player_init.c \
       src/engine/input_system.c \
       src/engine/event_system.c \
       src/engine/collision_system.c \
       src/engine/raycasting_engine.c \
       src/engine/ray_dda.c \
       src/engine/render_background.c \
       src/engine/wall_rendering.c

OBJS = $(patsubst src/%.c, $(OBJ_DIR)/%.o, $(SRCS))

HEADERS = include/cub3d.h
NAME = cub3D

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDES = -I./$(LIBFT_DIR) -I./include -I./$(MLX42_DIR)/include
LIBS = -L./$(LIBFT_DIR) -lft $(MLX42_LIB) $(MLX42_FLAGS)

GREEN = \033[1;32m
RESET = \033[0m

all: $(LIBFT) $(MLX42_LIB) $(OBJ_DIR) $(NAME)

$(NAME): $(OBJS) $(MLX42_LIB)
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

$(MLX42_LIB):
	@echo "$(GREEN)Building MLX42...$(RESET)"
	@if [ ! -d "$(MLX42_BUILD)" ]; then \
		cd $(MLX42_DIR) && cmake -B build -DDEBUG=1; \
	fi
	@$(MAKE) -C $(MLX42_BUILD)
	@echo "$(GREEN)MLX42 build complete!$(RESET)"

clean:
	@echo "$(GREEN)Cleaning...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) clean
	@if [ -d "$(MLX42_BUILD)" ]; then $(MAKE) -C $(MLX42_BUILD) clean; fi
	@$(RM) $(OBJS)
	@echo "$(GREEN)Clean complete.$(RESET)"

fclean: clean
	@echo "$(GREEN)Deleting $(NAME)...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -rf $(OBJ_DIR)
	@rm -rf $(MLX42_BUILD)
	@$(RM) $(NAME)
	@echo "$(GREEN)Deleted $(NAME)$(RESET)"

re: fclean all

.PHONY: all clean fclean re