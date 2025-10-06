/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggalle <anggalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:00:00 by anggalle          #+#    #+#             */
/*   Updated: 2025/10/06 12:21:26 by anggalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	flood_fill_check(t_config *config, int i, int j, char **visited)
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

int	init_visited_array(t_config *config, char **visited)
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

void	free_visited_array(char **visited, int height)
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

int	check_border_char(char c, int *result)
{
	if (c != '1' && c != ' ')
	{
		ft_putstr_fd("Error: Map border must be wall or space\n", 2);
		*result = -1;
		return (1);
	}
	return (0);
}

int	check_line_spacing(int only_spaces, int *found_map_content,
	int *empty_lines_count)
{
	if (only_spaces)
	{
		if (*found_map_content)
			(*empty_lines_count)++;
	}
	else
	{
		*found_map_content = 1;
		if (*empty_lines_count > 0)
		{
			ft_putstr_fd("Error: Map is not properly closed by walls\n", 2);
			return (-1);
		}
	}
	return (0);
}

int	validate_walls_loop(t_config *config, char **visited)
{
	int	i;

	i = -1;
	while (++i < config->map.height)
	{
		if (flood_fill_check(config, i, 0, visited) == -1
			|| flood_fill_check(config, i, (int)ft_strlen(config->map.grid[i])
				- 1, visited) == -1)
		{
			ft_putstr_fd("Error: Map is not properly closed by walls\n", 2);
			free_visited_array(visited, config->map.height);
			return (-1);
		}
	}
	return (0);
}
