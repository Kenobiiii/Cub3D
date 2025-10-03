/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_rendering.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paromero <paromero@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 19:53:09 by paromero          #+#    #+#             */
/*   Updated: 2025/10/03 09:19:56 by paromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	get_draw_bounds(t_game *game, t_ray *ray, int *start, int *end)
{
	*start = ray->draw_start;
	if (*start < 0)
		*start = 0;
	*end = ray->draw_end;
	if (*end >= game->win_height)
		*end = game->win_height - 1;
}

static int	calculate_tex_x(t_game *game, t_ray *ray)
{
	int	tex_x;

	tex_x = (int)(ray->wall_x * game->textures[ray->tex_num].width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= (int)game->textures[ray->tex_num].width)
		tex_x = game->textures[ray->tex_num].width - 1;
	if ((ray->side == 0 && ray->dir.x > 0)
		|| (ray->side == 1 && ray->dir.y < 0))
		tex_x = game->textures[ray->tex_num].width - tex_x - 1;
	return (tex_x);
}

static void	put_texture_pixel(t_game *game, int x, int y,
	t_texture_params *params)
{
	int	color;

	if (params->tex_x < 0 || params->tex_x >= (int)params->texture->width
		|| params->tex_y < 0 || params->tex_y >= (int)params->texture->height)
		return ;
	color = get_pixel(params->texture->img, params->tex_x, params->tex_y);
	mlx_put_pixel(game->screen.img, x, y, color);
}

static void	draw_texture_column(t_game *game, t_ray *ray, int x, int tex_x)
{
	int					y;
	int					tex_y;
	int					start;
	int					end;
	t_texture_params	params;

	get_draw_bounds(game, ray, &start, &end);
	y = start;
	while (y <= end)
	{
		tex_y = ((y - ray->draw_start) * game->textures[ray->tex_num].height)
			/ (ray->draw_end - ray->draw_start);
		if (tex_y >= (int)game->textures[ray->tex_num].height)
			tex_y = game->textures[ray->tex_num].height - 1;
		if (tex_y < 0)
			tex_y = 0;
		params.texture = &game->textures[ray->tex_num];
		params.tex_x = tex_x;
		params.tex_y = tex_y;
		put_texture_pixel(game, x, y, &params);
		y++;
	}
}

void	draw_wall_column(t_game *game, t_ray *ray, int x)
{
	int	tex_x;

	tex_x = calculate_tex_x(game, ray);
	draw_texture_column(game, ray, x, tex_x);
}
