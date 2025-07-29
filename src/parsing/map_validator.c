/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggalle <anggalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:00:00 by anggalle          #+#    #+#             */
/*   Updated: 2025/07/29 12:25:24 by anggalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Checks if a character is valid for the map
static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W' || c == ' ');
}

// Checks if a character represents the player
static int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

// Validates that all map characters are valid
static int	validate_characters(t_config *config)
{
	int	i;
	int	j;

	i = 0;
	while (i < config->map.height)
	{
		j = 0;
		while (config->map.grid[i][j])
		{
			if (!is_valid_char(config->map.grid[i][j]))
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

// Validates that there is exactly one player and stores its position
static int	validate_player(t_config *config)
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
	if (player_count != 1)
		return (-1);
	return (0);
}

// Main function that validates the complete map
int	validate_map(t_config *config)
{
	if (!config->map.grid || config->map.height <= 0)
		return (-1);
	if (validate_characters(config) == -1)
		return (-1);
	if (validate_player(config) == -1)
		return (-1);
	if (validate_walls(config) == -1)
		return (-1);
	return (0);
}
