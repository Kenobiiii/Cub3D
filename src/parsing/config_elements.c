/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggalle <anggalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:00:00 by anggalle          #+#    #+#             */
/*   Updated: 2025/07/29 13:17:48 by anggalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Processes and stores texture paths (NO, SO, WE, EA)
static int	process_texture(char *line, t_config *config)
{
	char	*path;

	path = ft_strtrim(line + 2, " \t");
	if (validate_path(path) == -1)
	{
		if (path)
			free(path);
		return (-1);
	}
	if (line[0] == 'N' && line[1] == 'O' && !config->no_path)
		config->no_path = path;
	else if (line[0] == 'S' && line[1] == 'O' && !config->so_path)
		config->so_path = path;
	else if (line[0] == 'W' && line[1] == 'E' && !config->we_path)
		config->we_path = path;
	else if (line[0] == 'E' && line[1] == 'A' && !config->ea_path)
		config->ea_path = path;
	else
	{
		free(path);
		return (-1);
	}
	return (0);
}

// Processes and stores floor and ceiling colors (F, C)
static int	process_color(char *line, t_config *config)
{
	int		color;
	char	*color_str;

	color_str = ft_strtrim(line + 1, " \t");
	if (validate_color_string(color_str) == -1)
	{
		if (color_str)
			free(color_str);
		return (-1);
	}
	color = parse_rgb(color_str);
	free(color_str);
	if (color == -1)
		return (-1);
	if (line[0] == 'F' && config->floor_color == -1)
		config->floor_color = color;
	else if (line[0] == 'C' && config->ceiling_color == -1)
		config->ceiling_color = color;
	else
		return (-1);
	return (0);
}

// Identifies and processes each configuration line
static int	process_line(char *line, t_config *config)
{
	if (!line || !*line)
		return (0);
	if (ft_strlen(line) < 2)
		return (-1);
	if ((line[0] == 'N' && line[1] == 'O') || (line[0] == 'S' && line[1] == 'O')
		|| (line[0] == 'W' && line[1] == 'E')
		|| (line[0] == 'E' && line[1] == 'A'))
		return (process_texture(line, config));
	else if (line[0] == 'F' || line[0] == 'C')
		return (process_color(line, config));
	return (-1);
}

// Reads all configuration elements until map is found
int	read_config_elements(int fd, t_config *config)
{
	char	*line;
	int		elements_count;

	elements_count = 0;
	while (elements_count < 6)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (ft_strlen(line) > 0)
		{
			if (process_line(line, config) == -1)
			{
				free(line);
				return (-1);
			}
			elements_count++;
		}
		free(line);
	}
	if (elements_count != 6)
		return (-1);
	return (0);
}
