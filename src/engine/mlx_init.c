/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paromero <paromero@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 10:36:04 by paromero          #+#    #+#             */
/*   Updated: 2025/10/15 11:18:55 by paromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	init_mlx_window(t_game *game)
{
	game->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT,
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
			WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->screen.img)
	{
		ft_putstr_fd("Error: Failed to create screen buffer\n", 2);
		mlx_terminate(game->mlx);
		return (-1);
	}
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
	mlx_close_hook(game->mlx, handle_close, game);
	if (load_textures(game) == -1)
	{
		ft_putstr_fd("Error: Failed to load textures\n", 2);
		mlx_terminate(game->mlx);
		return (-1);
	}
	init_player(game);
	mlx_loop_hook(game->mlx, game_update, game);
	printf("✅ MLX42 initialized successfully!\n");
	return (0);
}

int	close_game(t_game *game)
{
	cleanup_textures(game);
	if (game->screen.img)
	{
		mlx_delete_image(game->mlx, game->screen.img);
		game->screen.img = NULL;
	}
	if (game->mlx)
	{
		mlx_terminate(game->mlx);
		game->mlx = NULL;
	}
	free_config(&game->config);
	printf("✅ All resources freed\n");
	exit(0);
	return (0);
}
