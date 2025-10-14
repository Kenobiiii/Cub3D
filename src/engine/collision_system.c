/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_system.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 18:10:24 by paromero          #+#    #+#             */
/*   Updated: 2025/10/14 18:39:53 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	is_valid_position(t_game *game, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= game->config.map.width)
		return (0);
	if (map_y < 0 || map_y >= game->config.map.height)
		return (0);
	if (game->config.map.grid[map_y][map_x] == '1')
		return (0);
	return (1);
}

void	move_player(t_game *game, float new_x, float new_y)
{
	float	margin;
	float	test_x;
	float	test_y;

	margin = 0.3f;
	if (new_x > game->player.pos.x)
		test_x = new_x + margin;
	else
		test_x = new_x - margin;
	if (new_y > game->player.pos.y)
		test_y = new_y + margin;
	else
		test_y = new_y - margin;
	if (is_valid_position(game, test_x, game->player.pos.y))
		game->player.pos.x = new_x;
	if (is_valid_position(game, game->player.pos.x, test_y))
		game->player.pos.y = new_y;
}
