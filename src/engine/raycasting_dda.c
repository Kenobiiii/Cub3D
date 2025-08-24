/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_dda.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paromero <paromero@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 19:45:54 by paromero          #+#    #+#             */
/*   Updated: 2025/08/24 19:24:33 by paromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	perform_dda(t_ray *ray, t_game *game)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map_pos.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map_pos.y += ray->step.y;
			ray->side = 1;
		}
		if (game->config.map.grid[ray->map_pos.y][ray->map_pos.x] == '1')
			ray->hit = 1;
	}
}

void	calculate_wall_distance(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist.x - ray->delta_dist.x);
	else
		ray->perp_wall_dist = (ray->side_dist.y - ray->delta_dist.y);
}

void	determine_wall_texture(t_ray *ray)
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

void	cast_single_ray(t_ray *ray, t_game *game, int x)
{
	init_ray(ray, game, x);
	calculate_delta_dist(ray);
	calculate_step_and_side_dist(ray);
	perform_dda(ray, game);
	calculate_wall_distance(ray);
	determine_wall_texture(ray);
}
