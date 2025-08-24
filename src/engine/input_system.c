/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_system.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paromero <paromero@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 18:30:48 by paromero          #+#    #+#             */
/*   Updated: 2025/08/24 20:27:51 by paromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
		move_player_safe(game, new_x, new_y);
	}
	if (game->input.s)
	{
		new_x = game->player.pos.x - game->player.dir.x
			* game->player.move_speed;
		new_y = game->player.pos.y - game->player.dir.y
			* game->player.move_speed;
		move_player_safe(game, new_x, new_y);
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
		move_player_safe(game, new_x, new_y);
	}
	if (game->input.d)
	{
		new_x = game->player.pos.x - game->player.dir.y
			* game->player.move_speed;
		new_y = game->player.pos.y + game->player.dir.x
			* game->player.move_speed;
		move_player_safe(game, new_x, new_y);
	}
}

void	update_player_movement(t_game *game)
{
	handle_forward_movement(game);
	handle_strafe_movement(game);
}
