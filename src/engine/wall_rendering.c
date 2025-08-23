/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_rendering.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paromero <paromero@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 19:53:09 by paromero          #+#    #+#             */
/*   Updated: 2025/08/23 20:06:47 by paromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	calculate_wall_x(t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_x = ray->pos.y + ray->perp_wall_dist * ray->dir.y;
	else
		ray->wall_x = ray->pos.x + ray->perp_wall_dist * ray->dir.x;
	ray->wall_x -= (int)ray->wall_x;
	if (ray->wall_x < 0)
		ray->wall_x += 1.0f;
}

void	calculate_draw_limits(t_ray *ray, t_game *game, int *draw_start, 
	int *draw_end)
{
	int	line_height;

	if (ray->perp_wall_dist < 0.1f)
		ray->perp_wall_dist = 0.1f;
	line_height = (int)(game->win_height / ray->perp_wall_dist);
	if (line_height > game->win_height * 4)
		line_height = game->win_height * 4;
	*draw_start = -line_height / 2 + game->win_height / 2;
	if (*draw_start < 0)
		*draw_start = 0;
	*draw_end = line_height / 2 + game->win_height / 2;
	if (*draw_end >= game->win_height)
		*draw_end = game->win_height - 1;
}

void	draw_wall_column(t_game *game, t_ray *ray, int x)
{
	int		draw_start;
	int		draw_end;
	int		y;
	int		tex_x;
	int		tex_y;
	float	step;
	float	tex_pos;

	calculate_wall_x(ray);
	calculate_draw_limits(ray, game, &draw_start, &draw_end);
	tex_x = (int)(ray->wall_x * game->textures[ray->tex_num].width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= (int)game->textures[ray->tex_num].width)
		tex_x = game->textures[ray->tex_num].width - 1;
	if ((ray->side == 0 && ray->dir.x > 0) 
		|| (ray->side == 1 && ray->dir.y < 0))
		tex_x = game->textures[ray->tex_num].width - tex_x - 1;
	step = (float)game->textures[ray->tex_num].height / (draw_end - draw_start);
	tex_pos = (draw_start - game->win_height / 2 + (draw_end - draw_start) / 2) * step;
	y = draw_start;
	while (y < draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= (int)game->textures[ray->tex_num].height)
			tex_y = game->textures[ray->tex_num].height - 1;
		put_texture_pixel(game, x, y, &game->textures[ray->tex_num], 
			tex_x, tex_y);
		tex_pos += step;
		y++;
	}
}

void	render_frame(t_game *game)
{
	t_ray	ray;
	int		x;

	render_background(game);
	x = 0;
	while (x < game->win_width)
	{
		cast_single_ray(&ray, game, x);
		draw_wall_column(game, &ray, x);
		x++;
	}
}
