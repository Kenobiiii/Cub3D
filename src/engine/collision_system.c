/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_system.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paromero <paromero@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 18:10:24 by paromero          #+#    #+#             */
/*   Updated: 2025/10/06 10:26:52 by paromero         ###   ########.fr       */
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

static void	rotate_vectors(t_vector2f *dir, t_vector2f *fov, float angle)
{
	float	old_dir_x;
	float	old_fov_x;

	old_dir_x = dir->x;
	dir->x = dir->x * cos(angle) - dir->y * sin(angle);
	dir->y = old_dir_x * sin(angle) + dir->y * cos(angle);
	old_fov_x = fov->x;
	fov->x = fov->x * cos(angle) - fov->y * sin(angle);
	fov->y = old_fov_x * sin(angle) + fov->y * cos(angle);
}

void	update_player_rotation(t_game *game)
{
	if (game->input.left)
		rotate_vectors(&game->player.dir, &game->player.fov,
			-game->player.rot_speed);
	if (game->input.right)
		rotate_vectors(&game->player.dir, &game->player.fov,
			game->player.rot_speed);
}
