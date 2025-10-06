/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggalle <anggalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:00:00 by anggalle          #+#    #+#             */
/*   Updated: 2025/10/06 12:17:41 by anggalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		map_lines[i] = ft_strdup(line);
		if (!map_lines[i])
		{
			free(line);
			ft_putstr_fd("Error: Memory allocation failed\n", 2);
			return (-1);
		}
		i++;
		free(line);
	}
	return (i);
}

static int	pad_line(char **map_lines, int i, int max_width)
{
	char	*new_line;
	int		len;

	len = ft_strlen(map_lines[i]);
	if (len < max_width)
	{
		new_line = malloc(max_width + 1);
		if (!new_line)
		{
			free_array(map_lines);
			ft_putstr_fd("Error: Memory allocation failed\n", 2);
			return (-1);
		}
		ft_memcpy(new_line, map_lines[i], len);
		ft_memset(new_line + len, ' ', max_width - len);
		new_line[max_width] = '\0';
		free(map_lines[i]);
		map_lines[i] = new_line;
	}
	return (0);
}

static int	process_map_data(char **map_lines, int height, t_config *config)
{
	int	max_width;
	int	i;

	if (height <= 0)
	{
		free_array(map_lines);
		ft_putstr_fd("Error: Empty map\n", 2);
		return (-1);
	}
	map_lines[height] = NULL;
	find_max_width(map_lines, height, &max_width);
	i = 0;
	while (i < height)
	{
		if (pad_line(map_lines, i, max_width) == -1)
			return (-1);
		i++;
	}
	config->map.grid = map_lines;
	config->map.height = height;
	config->map.width = max_width;
	return (0);
}

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
