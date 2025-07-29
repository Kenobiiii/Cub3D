/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggalle <anggalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:00:00 by anggalle          #+#    #+#             */
/*   Updated: 2025/07/29 12:25:24 by anggalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Counts the number of map lines to allocate memory
static int	count_map_lines(int fd)
{
	char	*line;
	int		count;

	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (ft_strlen(line) > 0)
			count++;
		free(line);
	}
	return (count);
}

// Finds the maximum width of the map for alignment
static void	find_max_width(char **map_lines, int height, int *max_width)
{
	int	i;
	int	len;

	*max_width = 0;
	i = 0;
	while (i < height)
	{
		len = ft_strlen(map_lines[i]);
		if (len > *max_width)
			*max_width = len;
		i++;
	}
}

// Reads all map lines and stores them in memory
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
				return (-1);
			}
			i++;
		}
		free(line);
	}
	return (0);
}

// Reads and stores the complete map in the configuration structure
int	read_map(int fd, t_config *config)
{
	char	**map_lines;
	int		height;
	int		max_width;

	height = count_map_lines(fd);
	if (height <= 0)
		return (-1);
	map_lines = malloc(sizeof(char *) * (height + 1));
	if (!map_lines)
		return (-1);
	map_lines[height] = NULL;
	if (read_map_lines(fd, map_lines) == -1)
	{
		free_array(map_lines);
		return (-1);
	}
	find_max_width(map_lines, height, &max_width);
	config->map.grid = map_lines;
	config->map.height = height;
	config->map.width = max_width;
	return (0);
}
