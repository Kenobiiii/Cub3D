/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggalle <anggalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:31:32 by paromero          #+#    #+#             */
/*   Updated: 2025/07/29 13:56:24 by anggalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int ac, char **av)
{
	t_config	config;

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
	printf("File parsed successfully!\n");
	printf("Map dimensions: %dx%d\n", config.map.width, config.map.height);
	printf("Player position: (%.1f, %.1f) facing %c\n",
		config.player_start.x, config.player_start.y, config.player_dir);
	return (0);
}
