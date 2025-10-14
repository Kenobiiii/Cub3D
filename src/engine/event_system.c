/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_system.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 18:10:44 by paromero          #+#    #+#             */
/*   Updated: 2025/10/14 18:39:09 by pablo            ###   ########.fr       */
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
	render_background(game);
	raycasting_engine(game);
}
