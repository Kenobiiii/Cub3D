/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_basic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paromero <paromero@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 20:00:44 by paromero          #+#    #+#             */
/*   Updated: 2025/10/03 09:20:52 by paromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
