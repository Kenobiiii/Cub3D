/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paromero <paromero@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:31:32 by paromero          #+#    #+#             */
/*   Updated: 2025/08/02 18:25:59 by paromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int ac, char **av)
{
	t_config	config;
	t_game		game;

	if (ac != 2)
	{
		ft_putstr_fd("Error: Use: ./cub3D map.cub\n", 2);
		return (1);
	}
	config = parse_file(av[1]);
	if (config.map.grid == NULL)
	{
		ft_putstr_fd("Error: Failed to parse file\n", 2);
		return (1);
	}
	//TODO DEBUG
	printf("File parsed successfully!\n");
	printf("Map dimensions: %dx%d\n", config.map.width, config.map.height);
	printf("Player position: (%.1f, %.1f) facing %c\n",
		config.player_start.x, config.player_start.y, config.player_dir);
	//TODO END_DEBUG
	game.config = config;
	if (init_mlx42(&game) == -1)
	{
		ft_putstr_fd("Error: Failed to initialize MLX42\n", 2);
		return (1);
	}
	mlx_loop(game.mlx);
	return (0);
}
