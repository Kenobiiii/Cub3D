/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paromero <paromero@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:28:37 by paromero          #+#    #+#             */
/*   Updated: 2025/08/29 17:58:17 by paromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	set_north_direction(t_player *player)
{
	player->dir.x = 0.0f;
	player->dir.y = -1.0f;
	player->fov.x = 0.66f;
	player->fov.y = 0.0f;
}

static void	set_south_direction(t_player *player)
{
	player->dir.x = 0.0f;
	player->dir.y = 1.0f;
	player->fov.x = -0.66f;
	player->fov.y = 0.0f;
}

static void	set_east_west_direction(t_player *player, char direction)
{
	if (direction == 'E')
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

void	set_direction_vectors(t_player *player, char direction)
{
	if (direction == 'N')
		set_north_direction(player);
	else if (direction == 'S')
		set_south_direction(player);
	else
		set_east_west_direction(player, direction);
}

void	init_player(t_game *game)
{
	int	grid_x;
	int	grid_y;

	game->player.pos.x = game->config.player_start.x + 0.5f;
	game->player.pos.y = game->config.player_start.y + 0.5f;
	set_direction_vectors(&game->player, game->config.player_dir);
	game->player.move_speed = PLAYER_MOVE_SPEED;
	game->player.rot_speed = PLAYER_ROT_SPEED;
	grid_x = (int)game->player.pos.x;
	grid_y = (int)game->player.pos.y;
	if (grid_x < 0 || grid_x >= game->config.map.width
		|| grid_y < 0 || grid_y >= game->config.map.height
		|| game->config.map.grid[grid_y][grid_x] == '1')
	{
		ft_putstr_fd("Error: Invalid player position\n", 2);
	}
}
