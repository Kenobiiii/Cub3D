/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_dda.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paromero <paromero@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 18:11:01 by paromero          #+#    #+#             */
/*   Updated: 2025/09/30 09:30:11 by paromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

void	set_dda_params(t_ray *ray, t_game *game)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (game->player.pos.x - ray->map_pos.x)
			* ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map_pos.x + 1.0 - game->player.pos.x)
			* ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (game->player.pos.y - ray->map_pos.y)
			* ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map_pos.y + 1.0 - game->player.pos.y)
			* ray->delta_dist.y;
	}
}

void	perform_dda_algorithm(t_game *game, t_ray *ray)
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
		if (ray->map_pos.y < 0.25
			|| ray->map_pos.x < 0.25
			|| ray->map_pos.y > game->config.map.height - 0.25
			|| ray->map_pos.x > game->config.map.width - 1.25)
			break ;
		else if (game->config.map.grid[ray->map_pos.y][ray->map_pos.x] > '0')
			ray->hit = 1;
	}
}

void	calculate_line_height(t_ray *ray, t_game *game)
{
	int	line_height;

	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist.x - ray->delta_dist.x);
	else
		ray->perp_wall_dist = (ray->side_dist.y - ray->delta_dist.y);
	line_height = (int)(game->win_height / ray->perp_wall_dist);
	ray->draw_start = -line_height / 2 + game->win_height / 2;
	ray->draw_end = line_height / 2 + game->win_height / 2;
	if (ray->side == 0)
		ray->wall_x = game->player.pos.y + ray->perp_wall_dist * ray->dir.y;
	else
		ray->wall_x = game->player.pos.x + ray->perp_wall_dist * ray->dir.x;
	ray->wall_x -= floor(ray->wall_x);
}
