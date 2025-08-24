/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_basic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paromero <paromero@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 20:00:44 by paromero          #+#    #+#             */
/*   Updated: 2025/08/24 19:24:33 by paromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/cub3d.h"

void	put_pixel(mlx_image_t *img, int x, int y, int color)
{
	int	index;

	if (x < 0 || x >= (int)img->width || y < 0 || y >= (int)img->height)
		return ;
	index = (y * img->width + x) * 4;
	img->pixels[index + 0] = (color >> 24) & 0xFF;
	img->pixels[index + 1] = (color >> 16) & 0xFF;
	img->pixels[index + 2] = (color >> 8) & 0xFF;
	img->pixels[index + 3] = color & 0xFF;
}

int	get_pixel(mlx_image_t *img, int x, int y)
{
	int	index;
	int	r;
	int	g;
	int	b;
	int	a;

	if (x < 0 || x >= (int)img->width || y < 0 || y >= (int)img->height)
		return (0);
	index = (y * img->width + x) * 4;
	r = img->pixels[index + 0];
	g = img->pixels[index + 1];
	b = img->pixels[index + 2];
	a = img->pixels[index + 3];
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

int	create_rgba(int r, int g, int b, int a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

void	clear_screen(mlx_image_t *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < (int)img->height)
	{
		x = 0;
		while (x < (int)img->width)
		{
			put_pixel(img, x, y, 0x00000000);
			x++;
		}
		y++;
	}
}

void	draw_floor_ceiling(mlx_image_t *img, int floor_color, int ceiling_color)
{
	int	x;
	int	y;

	y = 0;
	while (y < (int)img->height)
	{
		x = 0;
		while (x < (int)img->width)
		{
			if (y < (int)img->height / 2)
				put_pixel(img, x, y, ceiling_color);
			else
				put_pixel(img, x, y, floor_color);
			x++;
		}
		y++;
	}
}

void	put_texture_pixel(t_game *game, int x, int y, t_texture *texture, 
	int tex_x, int tex_y)
{
	int	color;

	if (tex_x < 0 || tex_x >= (int)texture->width 
		|| tex_y < 0 || tex_y >= (int)texture->height)
		return ;
	color = get_pixel(texture->img, tex_x, tex_y);
	put_pixel(game->screen.img, x, y, color);
}
