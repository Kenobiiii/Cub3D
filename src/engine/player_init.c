/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paromero <paromero@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:28:37 by paromero          #+#    #+#             */
/*   Updated: 2025/10/03 11:10:23 by paromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	set_north_south_direction(t_player *player, char direction)
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

void	init_player(t_game *game)
{
	game->player.pos.x = game->config.player_start.x + 0.5f;
	game->player.pos.y = game->config.player_start.y + 0.5f;
	if (game->config.player_dir == 'N' || game->config.player_dir == 'S')
		set_north_south_direction(&game->player, game->config.player_dir);
	else
		set_east_west_direction(&game->player, game->config.player_dir);
	game->player.move_speed = PLAYER_MOVE_SPEED;
	game->player.rot_speed = PLAYER_ROT_SPEED;
}
