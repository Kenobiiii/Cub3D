/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_engine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paromero <paromero@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 19:37:09 by paromero          #+#    #+#             */
/*   Updated: 2025/08/29 17:58:17 by paromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <math.h>

static void	init_raycasting_info(int x, t_ray *ray, t_game *game)
{
	init_ray_data(ray);
	ray->camera_x = 2 * x / (double)game->win_width - 1;
	ray->dir.x = game->player.dir.x + game->player.fov.x * ray->camera_x;
	ray->dir.y = game->player.dir.y + game->player.fov.y * ray->camera_x;
	ray->map_pos.x = (int)game->player.pos.x;
	ray->map_pos.y = (int)game->player.pos.y;
	ray->delta_dist.x = fabs(1 / ray->dir.x);
	ray->delta_dist.y = fabs(1 / ray->dir.y);
}

int	raycasting_engine(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < game->win_width)
	{
		init_raycasting_info(x, &ray, game);
		set_dda_params(&ray, game);
		perform_dda_algorithm(game, &ray);
		calculate_line_height(&ray, game);
		determine_wall_texture(&ray);
		draw_wall_column(game, &ray, x);
		x++;
	}
	return (0);
}
