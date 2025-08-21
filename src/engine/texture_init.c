/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paromero <paromero@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 18:46:53 by paromero          #+#    #+#             */
/*   Updated: 2025/08/21 20:04:18 by paromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	load_single_texture(t_game *game, char *path, int index)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	if (!texture)
	{
		ft_printf("Error: Failed to load texture: %s\n", path);
		return (-1);
	}
	game->textures[index].img = mlx_texture_to_image(game->mlx, texture);
	if (!game->textures[index].img)
	{
		ft_printf("Error: Failed to convert texture to image: %s\n", path);
		mlx_delete_texture(texture);
		return (-1);
	}
	game->textures[index].width = texture->width;
	game->textures[index].height = texture->height;
	mlx_delete_texture(texture);
	return (0);
}

int	load_textures(t_game *game)
{
	if (load_single_texture(game, game->config.no_path, 0) == -1)
	{
		ft_putstr_fd("Error: Failed to load North texture\n", 2);
		return (-1);
	}
	if (load_single_texture(game, game->config.so_path, 1) == -1)
	{
		ft_putstr_fd("Error: Failed to load South texture\n", 2);
		return (-1);
	}
	if (load_single_texture(game, game->config.we_path, 2) == -1)
	{
		ft_putstr_fd("Error: Failed to load West texture\n", 2);
		return (-1);
	}
	if (load_single_texture(game, game->config.ea_path, 3) == -1)
	{
		ft_putstr_fd("Error: Failed to load East texture\n", 2);
		return (-1);
	}
	ft_printf("✅ All wall textures loaded successfully!\n");
	return (0);
}

void	cleanup_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->textures[i].img)
		{
			mlx_delete_image(game->mlx, game->textures[i].img);
			game->textures[i].img = NULL;
		}
		i++;
	}
	ft_printf("✅ All textures cleaned up\n");
}
