/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_rendering.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paromero <paromero@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 19:53:09 by paromero          #+#    #+#             */
/*   Updated: 2025/08/24 19:24:33 by paromero         ###   ########.fr       */
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
	int		y;
	int		tex_x;
	int		tex_y;
	int		start;
	int		end;

	tex_x = (int)(ray->wall_x * game->textures[ray->tex_num].width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= (int)game->textures[ray->tex_num].width)
		tex_x = game->textures[ray->tex_num].width - 1;
	if ((ray->side == 0 && ray->dir.x > 0) 
		|| (ray->side == 1 && ray->dir.y < 0))
		tex_x = game->textures[ray->tex_num].width - tex_x - 1;
	start = ray->draw_start;
	if (start < 0)
		start = 0;
	end = ray->draw_end;
	if (end >= game->win_height)
		end = game->win_height - 1;
	y = start;
	while (y <= end)
	{
		tex_y = ((y - ray->draw_start) * game->textures[ray->tex_num].height)
			/ (ray->draw_end - ray->draw_start);
		if (tex_y >= (int)game->textures[ray->tex_num].height)
			tex_y = game->textures[ray->tex_num].height - 1;
		if (tex_y < 0)
			tex_y = 0;
		put_texture_pixel(game, x, y, &game->textures[ray->tex_num], 
			tex_x, tex_y);
		y++;
	}
}

void	render_frame(t_game *game)
{
	render_background(game);
	raycasting_engine(game);
}
