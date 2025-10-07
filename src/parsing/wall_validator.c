/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_validator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paromero <paromero@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:00:00 by anggalle          #+#    #+#             */
/*   Updated: 2025/10/07 11:02:11 by paromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_line_spacing(int only_spaces, int *found_map_content,
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

static int	process_line_content(t_config *config, int i,
	int *found_map_content, int *empty_lines_count)
{
	int	j;
	int	only_spaces;

	only_spaces = 1;
	j = -1;
	while (config->map.grid[i][++j])
	{
		if (config->map.grid[i][j] != ' ' && config->map.grid[i][j] != '\0')
		{
			only_spaces = 0;
			break ;
		}
	}
	if (only_spaces || ft_strlen(config->map.grid[i]) == 0)
		only_spaces = 1;
	if (check_line_spacing(only_spaces, found_map_content,
			empty_lines_count) == -1)
		return (-1);
	return (0);
}

static int	check_isolated_content(t_config *config)
{
	int	i;
	int	empty_lines_count;
	int	found_map_content;

	empty_lines_count = 0;
	found_map_content = 0;
	i = -1;
	while (++i < config->map.height)
	{
		if (process_line_content(config, i, &found_map_content,
				&empty_lines_count) == -1)
			return (-1);
	}
	return (0);
}

static int	validate_map_borders(t_config *config)
{
	int	i;
	int	j;
	int	result;

	result = 0;
	i = -1;
	while (++i < config->map.height)
	{
		if (check_border_char(config->map.grid[i][0], &result))
			return (result);
		if (check_border_char(config->map.grid[i]
				[config->map.width - 1], &result))
			return (result);
	}
	j = -1;
	while (++j < config->map.width)
	{
		if (check_border_char(config->map.grid[0][j], &result))
			return (result);
		if (check_border_char(config->map.grid
				[config->map.height - 1][j], &result))
			return (result);
	}
	return (0);
}

int	validate_walls(t_config *config)
{
	char	**visited;
	int		result;

	if (check_isolated_content(config) == -1 || validate_map_borders(config)
		== -1)
		return (-1);
	visited = malloc(sizeof(char *) * config->map.height);
	if (!visited || init_visited_array(config, visited) == -1)
	{
		free(visited);
		return (-1);
	}
	if (validate_walls_loop(config, visited) == -1)
		return (-1);
	result = flood_fill_check(config, 0, 0, visited);
	free_visited_array(visited, config->map.height);
	if (result == -1)
	{
		ft_putstr_fd("Error: Map is not properly closed by walls\n", 2);
		return (-1);
	}
	return (0);
}
