/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_system.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paromero <paromero@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 18:30:48 by paromero          #+#    #+#             */
/*   Updated: 2025/08/23 20:06:47 by paromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <math.h>

void	update_input(t_game *game)
{
	game->input.w = mlx_is_key_down(game->mlx, MLX_KEY_W);
	game->input.s = mlx_is_key_down(game->mlx, MLX_KEY_S);
	game->input.a = mlx_is_key_down(game->mlx, MLX_KEY_A);
	game->input.d = mlx_is_key_down(game->mlx, MLX_KEY_D);
	game->input.left = mlx_is_key_down(game->mlx, MLX_KEY_LEFT);
	game->input.right = mlx_is_key_down(game->mlx, MLX_KEY_RIGHT);
	game->input.esc = mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE);
}

int	is_valid_position(t_game *game, float x, float y)
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

void	move_player_safe(t_game *game, float new_x, float new_y)
{
	float	margin;
	float	test_x;
	float	test_y;

	margin = 0.3f;
	test_x = new_x + (new_x > game->player.pos.x ? margin : -margin);
	test_y = new_y + (new_y > game->player.pos.y ? margin : -margin);
	if (is_valid_position(game, test_x, game->player.pos.y))
		game->player.pos.x = new_x;
	if (is_valid_position(game, game->player.pos.x, test_y))
		game->player.pos.y = new_y;
}

void	update_player_movement(t_game *game)
{
	float	new_x;
	float	new_y;

	if (game->input.w)
	{
		new_x = game->player.pos.x + game->player.dir.x * game->player.move_speed;
		new_y = game->player.pos.y + game->player.dir.y * game->player.move_speed;
		move_player_safe(game, new_x, new_y);
	}
	if (game->input.s)
	{
		new_x = game->player.pos.x - game->player.dir.x * game->player.move_speed;
		new_y = game->player.pos.y - game->player.dir.y * game->player.move_speed;
		move_player_safe(game, new_x, new_y);
	}
	if (game->input.a)
	{
		new_x = game->player.pos.x + game->player.dir.y * game->player.move_speed;
		new_y = game->player.pos.y - game->player.dir.x * game->player.move_speed;
		move_player_safe(game, new_x, new_y);
	}
	if (game->input.d)
	{
		new_x = game->player.pos.x - game->player.dir.y * game->player.move_speed;
		new_y = game->player.pos.y + game->player.dir.x * game->player.move_speed;
		move_player_safe(game, new_x, new_y);
	}
}

void	rotate_vectors(t_vector2f *dir, t_vector2f *fov, float angle)
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

void	game_update(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	update_input(game);
	if (game->input.esc)
		close_game(game);
	update_player_movement(game);
	update_player_rotation(game);
	render_frame(game);
}
