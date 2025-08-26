/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_validator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paromero <paromero@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:15:12 by anggalle          #+#    #+#             */
/*   Updated: 2025/08/26 19:31:33 by paromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Checks if a character represents the player
static int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

// Counts players and stores position of the first one found
static int	count_and_store_player(t_config *config)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = 0;
	while (i < config->map.height)
	{
		j = 0;
		while (config->map.grid[i][j])
		{
			if (is_player_char(config->map.grid[i][j]))
			{
				player_count++;
				config->player_start.x = j;
				config->player_start.y = i;
				config->player_dir = config->map.grid[i][j];
				config->map.grid[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	return (player_count);
}

// Validates that there is exactly one player and stores its position
int	validate_player(t_config *config)
{
	int	player_count;
	int	px;
	int	py;
	int	rowlen;

	player_count = count_and_store_player(config);
	if (player_count == -1)
	{
		ft_putstr_fd("Error: Invalid player configuration\n", 2);
		return (-1);
	}
	if (player_count != 1)
	{
		ft_putstr_fd("Error: Map must have exactly one player\n", 2);
		return (-1);
	}
	px = (int)config->player_start.x;
	py = (int)config->player_start.y;
	rowlen = ft_strlen(config->map.grid[py]);
	printf("DEBUG: Player at (%d, %d) of rowlen %d, map height %d\n", px, py, rowlen, config->map.height);
	if (px == 0 || py == 0 || py == config->map.height - 1
		|| px == rowlen - 1)
	{
		ft_putstr_fd("Error: Player cannot be on the edge of the map\n", 2);
		return (-1);
	}
	return (0);
}
