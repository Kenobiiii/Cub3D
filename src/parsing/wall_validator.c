/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_validator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggalle <anggalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:00:00 by anggalle          #+#    #+#             */
/*   Updated: 2025/07/29 14:17:32 by anggalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Returns the character at (i, j) or ' ' if out of bounds
static char	get_map_char(t_config *config, int i, int j)
{
	if (i < 0 || i >= config->map.height)
		return (' ');
	if (j < 0 || j >= (int)ft_strlen(config->map.grid[i]))
		return (' ');
	return (config->map.grid[i][j]);
}

// Checks that '0' and player are not adjacent to spaces or out of bounds
static int	validate_cell_closed(t_config *config, int i, int j)
{
	char	c;
	char	up_char;
	char	down_char;
	char	left_char;
	char	right_char;

	c = get_map_char(config, i, j);
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		up_char    = get_map_char(config, i - 1, j);
		down_char  = get_map_char(config, i + 1, j);
		left_char  = get_map_char(config, i, j - 1);
		right_char = get_map_char(config, i, j + 1);
		if (up_char == ' ' || down_char == ' ' || left_char == ' ' || right_char == ' ')
		{
			ft_putstr_fd("Error: Map is not properly closed by walls\n", 2);
			return (-1);
		}
	}
	return (0);
}

// Main wall validation function
int validate_walls(t_config *config)
{
	int i, j;
	for (i = 0; i < config->map.height; i++)
	{
		for (j = 0; j < (int)ft_strlen(config->map.grid[i]); j++)
		{
			if (validate_cell_closed(config, i, j) == -1)
				return -1;
		}
	}
	return 0;
}
