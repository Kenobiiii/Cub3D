/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_system.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paromero <paromero@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 18:10:44 by paromero          #+#    #+#             */
/*   Updated: 2025/09/24 18:35:06 by paromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	handle_keypress(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		printf("ESC pressed. Closing game...\n");
		close_game(game);
	}
}

void	handle_close(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	printf("Window closed.\n");
	close_game(game);
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
	raycasting_engine(game);
}
