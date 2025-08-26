/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paromero <paromero@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:28:37 by paromero          #+#    #+#             */
/*   Updated: 2025/08/26 20:20:05 by paromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
		ft_putstr_fd("Error: Invalid player position\n", 2);
	}
}
