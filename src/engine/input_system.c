/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_system.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paromero <paromero@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 18:30:48 by paromero          #+#    #+#             */
/*   Updated: 2025/10/15 10:59:17 by paromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

static void	handle_forward_movement(t_game *game, int w, int s)
{
	float	new_x;
	float	new_y;

	if (w)
	{
		new_x = game->player.pos.x + game->player.dir.x
			* game->player.move_speed;
		new_y = game->player.pos.y + game->player.dir.y
			* game->player.move_speed;
		move_player(game, new_x, new_y);
	}
	if (s)
	{
		new_x = game->player.pos.x - game->player.dir.x
			* game->player.move_speed;
		new_y = game->player.pos.y - game->player.dir.y
			* game->player.move_speed;
		move_player(game, new_x, new_y);
	}
}

static void	handle_strafe_movement(t_game *game, int a, int d)
{
	float	new_x;
	float	new_y;

	if (a)
	{
		new_x = game->player.pos.x + game->player.dir.y
			* game->player.move_speed;
		new_y = game->player.pos.y - game->player.dir.x
			* game->player.move_speed;
		move_player(game, new_x, new_y);
	}
	if (d)
	{
		new_x = game->player.pos.x - game->player.dir.y
			* game->player.move_speed;
		new_y = game->player.pos.y + game->player.dir.x
			* game->player.move_speed;
		move_player(game, new_x, new_y);
	}
}

void	update_input(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_vectors(&game->player.dir, &game->player.fov,
			-game->player.rot_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_vectors(&game->player.dir, &game->player.fov,
			game->player.rot_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		close_game(game);
	handle_forward_movement(game, mlx_is_key_down(game->mlx, MLX_KEY_W),
		mlx_is_key_down(game->mlx, MLX_KEY_S));
	handle_strafe_movement(game, mlx_is_key_down(game->mlx, MLX_KEY_A),
		mlx_is_key_down(game->mlx, MLX_KEY_D));
}
