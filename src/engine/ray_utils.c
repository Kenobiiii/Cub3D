/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paromero <paromero@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 12:00:00 by paromero          #+#    #+#             */
/*   Updated: 2025/08/24 20:27:51 by paromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_ray_data(t_ray *ray)
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
