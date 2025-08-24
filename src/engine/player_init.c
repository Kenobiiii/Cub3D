/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paromero <paromero@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:28:37 by paromero          #+#    #+#             */
/*   Updated: 2025/08/24 19:24:33 by paromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	set_direction_vectors(t_player *player, char direction)
{
	if (direction == 'N')
	{
		player->dir.x = 0.0f;
		player->dir.y = -1.0f;
		player->fov.x = 0.66f;
		player->fov.y = 0.0f;
	}
	else if (direction == 'S')
	{
		player->dir.x = 0.0f;
		player->dir.y = 1.0f;
		player->fov.x = -0.66f;
		player->fov.y = 0.0f;
	}
	else if (direction == 'E')
	{
		player->dir.x = 1.0f;
		player->dir.y = 0.0f;
		player->fov.x = 0.0f;
		player->fov.y = 0.66f;
	}
	else if (direction == 'W')
	{
		player->dir.x = -1.0f;
		player->dir.y = 0.0f;
		player->fov.x = 0.0f;
		player->fov.y = -0.66f;
	}
}

int	validate_player_position(t_game *game)
{
	int	grid_x;
	int	grid_y;

	grid_x = (int)game->player.pos.x;
	grid_y = (int)game->player.pos.y;
	if (grid_x < 0 || grid_x >= game->config.map.width)
		return (-1);
	if (grid_y < 0 || grid_y >= game->config.map.height)
		return (-1);
	if (game->config.map.grid[grid_y][grid_x] == '1')
		return (-1);
	return (0);
}

void	init_player(t_game *game)
{
	game->player.pos.x = game->config.player_start.x + 0.5f;
	game->player.pos.y = game->config.player_start.y + 0.5f;
	set_direction_vectors(&game->player, game->config.player_dir);
	game->player.move_speed = PLAYER_MOVE_SPEED;
	game->player.rot_speed = PLAYER_ROT_SPEED;
	if (validate_player_position(game) == -1)
	{
		printf("Warning: Player position validation failed\n");
	}
	printf("Player initialized at (%.2f, %.2f) facing %c\n", 
		game->player.pos.x, game->player.pos.y, game->config.player_dir);
	printf("   Direction: (%.2f, %.2f), FOV: (%.2f, %.2f)\n", 
		game->player.dir.x, game->player.dir.y, game->player.fov.x, game->player.fov.y);
}
