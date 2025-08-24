/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paromero <paromero@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 00:00:00 by paromero          #+#    #+#             */
/*   Updated: 2025/08/24 20:27:51 by paromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	init_mlx_window(t_game *game)
{
	game->win_width = WINDOW_WIDTH;
	game->win_height = WINDOW_HEIGHT;
	game->mlx = mlx_init(game->win_width, game->win_height,
			WINDOW_TITLE, false);
	if (!game->mlx)
	{
		ft_putstr_fd("Error: Failed to initialize MLX42\n", 2);
		return (-1);
	}
	return (0);
}

static int	init_screen_buffer(t_game *game)
{
	game->screen.img = mlx_new_image(game->mlx,
			game->win_width, game->win_height);
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
	return (0);
}

int	init_mlx42(t_game *game)
{
	if (init_mlx_window(game) == -1)
		return (-1);
	if (init_screen_buffer(game) == -1)
		return (-1);
	mlx_key_hook(game->mlx, handle_keypress, game);
	mlx_close_hook(game->mlx, handle_close, game);
	if (load_textures(game) == -1)
	{
		ft_putstr_fd("Error: Failed to load textures\n", 2);
		mlx_terminate(game->mlx);
		return (-1);
	}
	init_player(game);
	render_background(game);
	mlx_loop_hook(game->mlx, game_update, game);
	mlx_loop(game->mlx);
	printf("✅ MLX42 initialized successfully!\n");
	printf("   Window size: %dx%d\n", game->win_width, game->win_height);
	printf("   Press ESC to close\n");
	return (0);
}

int	close_game(t_game *game)
{
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
