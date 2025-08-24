/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paromero <paromero@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 12:00:00 by paromero          #+#    #+#             */
/*   Updated: 2025/08/24 12:00:00 by paromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <math.h>

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

static void	set_dda_params(t_ray *ray, t_game *game)
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

static void	perform_dda_algorithm(t_game *game, t_ray *ray)
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

static void	calculate_line_height(t_ray *ray, t_game *game)
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
