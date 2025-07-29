/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggalle <anggalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:00:00 by anggalle          #+#    #+#             */
/*   Updated: 2025/07/29 14:13:22 by anggalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Finds the maximum width of the map for alignment
static void	find_max_width(char **map_lines, int height, int *max_width)
{
	int	i;
	int	len;

	*max_width = 0;
	i = 0;
	while (i < height)
	{
		if (map_lines[i])
		{
			len = ft_strlen(map_lines[i]);
			if (len > *max_width)
				*max_width = len;
		}
		i++;
	}
}

// Reads all map lines from file
static int	read_map_lines(int fd, char **map_lines)
{
	char	*line;
	int		i;

	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (ft_strlen(line) > 0)
		{
			map_lines[i] = ft_strdup(line);
			if (!map_lines[i])
			{
				free(line);
				ft_putstr_fd("Error: Memory allocation failed\n", 2);
				return (-1);
			}
			i++;
		}
		free(line);
	}
	return (i);
}

// Processes the map after reading lines
static int	process_map_data(char **map_lines, int height, t_config *config)
{
	int	max_width;

	if (height <= 0)
	{
		free_array(map_lines);
		ft_putstr_fd("Error: Empty map\n", 2);
		return (-1);
	}
	map_lines[height] = NULL;
	find_max_width(map_lines, height, &max_width);
	config->map.grid = map_lines;
	config->map.height = height;
	config->map.width = max_width;
	return (0);
}

// Reads and stores the complete map in the configuration structure
int	read_map(int fd, t_config *config)
{
	char	**map_lines;
	int		height;

	map_lines = malloc(sizeof(char *) * 1000);
	if (!map_lines)
	{
		ft_putstr_fd("Error: Memory allocation failed\n", 2);
		return (-1);
	}
	height = read_map_lines(fd, map_lines);
	if (height == -1)
	{
		free_array(map_lines);
		return (-1);
	}
	return (process_map_data(map_lines, height, config));
}
