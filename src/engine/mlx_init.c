/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paromero <paromero@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 00:00:00 by paromero          #+#    #+#             */
/*   Updated: 2025/08/21 18:51:08 by paromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Maneja eventos de teclado
void handle_keypress(mlx_key_data_t keydata, void *param)
{
	t_game *game = (t_game *)param;

	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		printf("ESC pressed. Closing game...\n");
		close_game(game);
	}
}

// Maneja el cierre de ventana
void handle_close(void *param)
{
	t_game *game = (t_game *)param;
	printf("Window closed.\n");
	close_game(game);
}

// Inicializa MLX42 y crea la ventana
int init_mlx42(t_game *game)
{
	game->win_width = 800;
	game->win_height = 600;
	game->mlx = mlx_init(game->win_width, game->win_height, "CUB3D", false);
	if (!game->mlx)
	{
		ft_putstr_fd("Error: Failed to initialize MLX42\n", 2);
		return (-1);
	}
	game->screen.img = mlx_new_image(game->mlx, game->win_width, game->win_height);
	if (!game->screen.img)
	{
		ft_putstr_fd("Error: Failed to create screen buffer\n", 2);
		mlx_terminate(game->mlx);
		return (-1);
	}
	game->screen.width = game->win_width;
	game->screen.height = game->win_height;
	if (mlx_image_to_window(game->mlx, game->screen.img, 0, 0) == -1)
	{
		ft_putstr_fd("Error: Failed to display screen buffer\n", 2);
		mlx_terminate(game->mlx);
		return (-1);
	}
	mlx_key_hook(game->mlx, handle_keypress, game);
	mlx_close_hook(game->mlx, handle_close, game);
	
	// Cargar texturas de las paredes
	if (load_textures(game) == -1)
	{
		ft_putstr_fd("Error: Failed to load textures\n", 2);
		mlx_terminate(game->mlx);
		return (-1);
	}
	
	printf("✅ MLX42 initialized successfully!\n");
	printf("   Window size: %dx%d\n", game->win_width, game->win_height);
	printf("   Press ESC to close\n");
	return (0);
}

// Libera recursos de MLX42
int close_game(t_game *game)
{
	// Limpiar texturas primero
	cleanup_textures(game);
	
	if (game->mlx)
	{
		mlx_terminate(game->mlx);
		game->mlx = NULL;
	}
	
	printf("✅ MLX42 resources freed\n");
	exit(0);
	return (0);
}
