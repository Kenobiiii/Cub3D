/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_engine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggalle <anggalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 19:37:09 by paromero          #+#    #+#             */
/*   Updated: 2025/10/08 18:08:32 by anggalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	determine_wall_texture(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->step.x == 1)
			ray->tex_num = 2;
		else
			ray->tex_num = 3;
	}
	else
	{
		if (ray->step.y == 1)
			ray->tex_num = 1;
		else
			ray->tex_num = 0;
	}
}

static void	init_ray_data(t_ray *ray)
{
	ray->camera_x = 0;
	ray->dir.x = 0;
	ray->dir.y = 0;
	ray->map_pos.x = 0;
	ray->map_pos.y = 0;
	ray->step.x = 0;
	ray->step.y = 0;
	ray->side_dist.x = 0;
	ray->side_dist.y = 0;
	ray->delta_dist.x = 0;
	ray->delta_dist.y = 0;
	ray->perp_wall_dist = 0;
	ray->wall_x = 0;
	ray->side = 0;
	ray->hit = 0;
}

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
	int		column;

	column = 0;
	while (column < game->win_width)
	{
		init_raycasting_info(column, &ray, game);
		set_dda_params(&ray, game);
		perform_dda_algorithm(game, &ray);
		calculate_line_height(&ray, game);
		determine_wall_texture(&ray);
		draw_texture_column(game, &ray, column, calculate_tex_x(game, &ray));
		column++;
	}
	return (0);
}
