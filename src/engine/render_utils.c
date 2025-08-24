/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paromero <paromero@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 19:25:00 by paromero          #+#    #+#             */
/*   Updated: 2025/08/24 20:31:03 by paromero         ###   ########.fr       */
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

void	put_texture_pixel(t_game *game, int x, int y, t_texture_params *params)
{
	int	color;

	if (params->tex_x < 0 || params->tex_x >= (int)params->texture->width
		|| params->tex_y < 0 || params->tex_y >= (int)params->texture->height)
		return ;
	color = get_pixel(params->texture->img, params->tex_x, params->tex_y);
	put_pixel(game->screen.img, x, y, color);
}

void	draw_texture_column(t_game *game, t_ray *ray, int x, int tex_x)
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

void	draw_texture_loop(t_game *game, t_ray *ray, int x, int tex_x)
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
