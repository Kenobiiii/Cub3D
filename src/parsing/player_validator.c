/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_validator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggalle <anggalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:15:12 by anggalle          #+#    #+#             */
/*   Updated: 2025/07/29 14:17:24 by anggalle         ###   ########.fr       */
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

	player_count = count_and_store_player(config);
	if (player_count == 0)
	{
		ft_putstr_fd("Error: No player found in map\n", 2);
		return (-1);
	}
	if (player_count > 1)
	{
		ft_putstr_fd("Error: Multiple players found in map\n", 2);
		return (-1);
	}
	return (0);
}