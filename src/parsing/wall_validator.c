/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_validator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggalle <anggalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:00:00 by anggalle          #+#    #+#             */
/*   Updated: 2025/07/29 15:55:33 by anggalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Flood fill from outside to check if map is properly closed
static int	flood_fill_check(t_config *config, int i, int j, char **visited)
{
	char	c;

	if (i < 0 || i >= config->map.height || j < 0 
		|| j >= (int)ft_strlen(config->map.grid[i]))
		return (0);
	if (visited[i][j] == '1')
		return (0);
	c = config->map.grid[i][j];
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (-1);
	if (c == '1')
		return (0);
	visited[i][j] = '1';
	if (flood_fill_check(config, i - 1, j, visited) == -1)
		return (-1);
	if (flood_fill_check(config, i + 1, j, visited) == -1)
		return (-1);
	if (flood_fill_check(config, i, j - 1, visited) == -1)
		return (-1);
	if (flood_fill_check(config, i, j + 1, visited) == -1)
		return (-1);
	return (0);
}

// Checks for any content after the main map area
static int	check_isolated_content(t_config *config)
{
	int	i;
	int	empty_lines_count;
	int	found_map_content;

	empty_lines_count = 0;
	found_map_content = 0;
	i = 0;
	while (i < config->map.height)
	{
		int	j;
		int	only_spaces;

		only_spaces = 1;
		j = 0;
		while (config->map.grid[i][j])
		{
			if (config->map.grid[i][j] != ' ' && config->map.grid[i][j] != '\0')
			{
				only_spaces = 0;
				break ;
			}
			j++;
		}
		if (only_spaces || ft_strlen(config->map.grid[i]) == 0)
		{
			if (found_map_content)
				empty_lines_count++;
		}
		else
		{
			found_map_content = 1;
			if (empty_lines_count > 0)
			{
				ft_putstr_fd("Error: Map is not properly closed by walls\n", 2);
				return (-1);
			}
		}
		i++;
	}
	return (0);
}

// Checks that the borders of the map are only '1' or ' '
static int	validate_map_borders(t_config *config)
{
	int i;
	int j;
	int w = config->map.width;
	int h = config->map.height;

	i = 0;
	while (i < h)
	{
		if (config->map.grid[i][0] != '1' && config->map.grid[i][0] != ' ')
		{
			ft_putstr_fd("Error: Map border must be wall or space\n", 2);
			return (-1);
		}
		if (config->map.grid[i][w - 1] != '1' && config->map.grid[i][w - 1] != ' ')
		{
			ft_putstr_fd("Error: Map border must be wall or space\n", 2);
			return (-1);
		}
		i++;
	}
	j = 0;
	while (j < w)
	{
		if (config->map.grid[0][j] != '1' && config->map.grid[0][j] != ' ')
		{
			ft_putstr_fd("Error: Map border must be wall or space\n", 2);
			return (-1);
		}
		if (config->map.grid[h - 1][j] != '1' && config->map.grid[h - 1][j] != ' ')
		{
			ft_putstr_fd("Error: Map border must be wall or space\n", 2);
			return (-1);
		}
		j++;
	}
	return (0);
}

// Initializes visited array for flood fill
static int	init_visited_array(t_config *config, char **visited)
{
	int	i;

	i = 0;
	while (i < config->map.height)
	{
		visited[i] = malloc(sizeof(char) * 1000);
		if (!visited[i])
			return (-1);
		ft_memset(visited[i], 0, 1000);
		i++;
	}
	return (0);
}

// Frees visited array
static void	free_visited_array(char **visited, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

// Main wall validation function using flood fill
int	validate_walls(t_config *config)
{
	char	**visited;
	int		i;
	int		result;

	if (check_isolated_content(config) == -1)
		return (-1);
	if (validate_map_borders(config) == -1)
		return (-1);
	visited = malloc(sizeof(char *) * config->map.height);
	if (!visited)
		return (-1);
	if (init_visited_array(config, visited) == -1)
	{
		free(visited);
		return (-1);
	}
	i = 0;
	while (i < config->map.height)
	{
		if (flood_fill_check(config, i, 0, visited) == -1
			|| flood_fill_check(config, i, 
				(int)ft_strlen(config->map.grid[i]) - 1, visited) == -1)
		{
			ft_putstr_fd("Error: Map is not properly closed by walls\n", 2);
			free_visited_array(visited, config->map.height);
			return (-1);
		}
		i++;
	}
	result = flood_fill_check(config, 0, 0, visited);
	free_visited_array(visited, config->map.height);
	if (result == -1)
	{
		ft_putstr_fd("Error: Map is not properly closed by walls\n", 2);
		return (-1);
	}
	return (0);
}

