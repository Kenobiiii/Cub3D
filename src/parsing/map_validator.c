/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggalle <anggalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:00:00 by anggalle          #+#    #+#             */
/*   Updated: 2025/07/29 14:17:27 by anggalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Checks if a character is valid for the map
static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W' || c == ' ');
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
			{
				ft_putstr_fd("Error: Invalid character in map\n", 2);
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

// Main function that validates the complete map
int	validate_map(t_config *config)
{
	if (!config->map.grid || config->map.height <= 0)
	{
		ft_putstr_fd("Error: Empty or invalid map\n", 2);
		return (-1);
	}
	if (validate_characters(config) == -1)
		return (-1);
	if (validate_player(config) == -1)
		return (-1);
	if (validate_walls(config) == -1)
	{
		ft_putstr_fd("Error: Map is not properly closed by walls\n", 2);
		return (-1);
	}
	return (0);
}
