/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_background.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paromero <paromero@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 18:00:00 by paromero          #+#    #+#             */
/*   Updated: 2025/08/29 18:00:00 by paromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	convert_rgb_to_mlx(int rgb_color)
{
	int	r;
	int	g;
	int	b;

	r = (rgb_color >> 16) & 0xFF;
	g = (rgb_color >> 8) & 0xFF;
	b = rgb_color & 0xFF;
	return (create_rgba(r, g, b, 255));
}

void	render_background(t_game *game)
{
	int	floor_color;
	int	ceiling_color;

	floor_color = convert_rgb_to_mlx(game->config.floor_color);
	ceiling_color = convert_rgb_to_mlx(game->config.ceiling_color);
	draw_floor_ceiling(game->screen.img, floor_color, ceiling_color);
}
