/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paromero <paromero@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 19:45:00 by paromero          #+#    #+#             */
/*   Updated: 2025/08/23 19:53:48 by paromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <math.h>

void	init_ray(t_ray *ray, t_game *game, int x)
{
	float	camera_x;

	camera_x = 2.0 * x / (float)game->win_width - 1.0;
	ray->dir.x = game->player.dir.x + camera_x * game->player.fov.x;
	ray->dir.y = game->player.dir.y + camera_x * game->player.fov.y;
	ray->pos.x = game->player.pos.x;
	ray->pos.y = game->player.pos.y;
	ray->hit = 0;
}

void	calculate_delta_dist(t_ray *ray)
{
	if (ray->dir.x == 0)
		ray->delta_dist.x = 1e30;
	else
		ray->delta_dist.x = fabs(1.0 / ray->dir.x);
	if (ray->dir.y == 0)
		ray->delta_dist.y = 1e30;
	else
		ray->delta_dist.y = fabs(1.0 / ray->dir.y);
}

void	calculate_step_and_side_dist(t_ray *ray)
{
	ray->map_pos.x = (int)ray->pos.x;
	ray->map_pos.y = (int)ray->pos.y;
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (ray->pos.x - ray->map_pos.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map_pos.x + 1.0 - ray->pos.x) 
			* ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (ray->pos.y - ray->map_pos.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map_pos.y + 1.0 - ray->pos.y) 
			* ray->delta_dist.y;
	}
}
