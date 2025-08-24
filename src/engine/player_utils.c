/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paromero <paromero@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 12:00:00 by paromero          #+#    #+#             */
/*   Updated: 2025/08/24 20:27:51 by paromero         ###   ########.fr       */
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

static void	set_east_direction(t_player *player)
{
	player->dir.x = 1.0f;
	player->dir.y = 0.0f;
	player->fov.x = 0.0f;
	player->fov.y = 0.66f;
}

static void	set_west_direction(t_player *player)
{
	player->dir.x = -1.0f;
	player->dir.y = 0.0f;
	player->fov.x = 0.0f;
	player->fov.y = -0.66f;
}

void	set_direction_vectors(t_player *player, char direction)
{
	if (direction == 'N')
		set_north_direction(player);
	else if (direction == 'S')
		set_south_direction(player);
	else if (direction == 'E')
		set_east_direction(player);
	else if (direction == 'W')
		set_west_direction(player);
}
