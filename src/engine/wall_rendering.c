/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_rendering.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paromero <paromero@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 19:53:09 by paromero          #+#    #+#             */
/*   Updated: 2025/08/24 20:27:51 by paromero         ###   ########.fr       */
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

void	draw_wall_column(t_game *game, t_ray *ray, int x)
{
	int	tex_x;

	tex_x = calculate_tex_x(game, ray);
	draw_texture_column(game, ray, x, tex_x);
}
