/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_system.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 18:30:48 by paromero          #+#    #+#             */
/*   Updated: 2025/10/14 18:40:28 by pablo            ###   ########.fr       */
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

static void	update_player_rotation(t_game *game)
{
	if (game->input.left)
		rotate_vectors(&game->player.dir, &game->player.fov,
			-game->player.rot_speed);
	if (game->input.right)
		rotate_vectors(&game->player.dir, &game->player.fov,
			game->player.rot_speed);
}

static void	handle_forward_movement(t_game *game)
{
	float	new_x;
	float	new_y;

	if (game->input.w)
	{
		new_x = game->player.pos.x + game->player.dir.x
			* game->player.move_speed;
			new_y = game->player.pos.y + game->player.dir.y
			* game->player.move_speed;
			move_player(game, new_x, new_y);
	}
	if (game->input.s)
	{
		new_x = game->player.pos.x - game->player.dir.x
		* game->player.move_speed;
		new_y = game->player.pos.y - game->player.dir.y
		* game->player.move_speed;
		move_player(game, new_x, new_y);
	}
}

static void	handle_strafe_movement(t_game *game)
{
	float	new_x;
	float	new_y;

	if (game->input.a)
	{
		new_x = game->player.pos.x + game->player.dir.y
			* game->player.move_speed;
			new_y = game->player.pos.y - game->player.dir.x
			* game->player.move_speed;
		move_player(game, new_x, new_y);
	}
	if (game->input.d)
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
	game->input.w = mlx_is_key_down(game->mlx, MLX_KEY_W);
	game->input.s = mlx_is_key_down(game->mlx, MLX_KEY_S);
	game->input.a = mlx_is_key_down(game->mlx, MLX_KEY_A);
	game->input.d = mlx_is_key_down(game->mlx, MLX_KEY_D);
	game->input.left = mlx_is_key_down(game->mlx, MLX_KEY_LEFT);
	game->input.right = mlx_is_key_down(game->mlx, MLX_KEY_RIGHT);
	game->input.esc = mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE);
	handle_forward_movement(game);
	handle_strafe_movement(game);
	update_player_rotation(game);
}
