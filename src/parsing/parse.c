/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggalle <anggalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:00:00 by anggalle          #+#    #+#             */
/*   Updated: 2025/10/08 17:34:35 by anggalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Validates that the file has .cub extension
static int	validate_file_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 5)
	{
		ft_putstr_fd("Error: File name too short\n", 2);
		return (-1);
	}
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
	{
		ft_putstr_fd("Error: File must have .cub extension\n", 2);
		return (-1);
	}
	return (0);
}

// Initializes the configuration structure with default values
static t_config	init_config(void)
{
	t_config	config;

	config.no_path = NULL;
	config.so_path = NULL;
	config.we_path = NULL;
	config.ea_path = NULL;
	config.floor_color = -1;
	config.ceiling_color = -1;
	config.map_path = NULL;
	config.map.grid = NULL;
	config.map.width = 0;
	config.map.height = 0;
	config.player_start.x = 0;
	config.player_start.y = 0;
	config.player_dir = '\0';
	return (config);
}

// Opens the .cub file and handles opening errors
static int	open_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error: Cannot open file\n", 2);
		return (-1);
	}
	return (fd);
}

// Processes the file once opened and validates its content
static int	process_file(int fd, t_config *config)
{
	if (read_config_elements(fd, config) == -1)
	{
		ft_putstr_fd("Error: Invalid configuration elements\n", 2);
		return (-1);
	}
	if (read_map(fd, config) == -1)
	{
		ft_putstr_fd("Error: Invalid map\n", 2);
		return (-1);
	}
	if (validate_map(config) == -1)
	{
		ft_putstr_fd("Error: Map validation failed\n", 2);
		return (-1);
	}
	return (0);
}

// Main function that parses the entire .cub file
t_config	parse_file(char *filename)
{
	t_config	config;
	int			fd;
	char		*line;

	config = init_config();
	if (validate_file_extension(filename) == -1)
		return (config);
	fd = open_file(filename);
	if (fd == -1)
		return (config);
	if (process_file(fd, &config) == -1)
	{
		line = get_next_line(fd);
		while (line)
		{
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
		free_config(&config);
		return (config);
	}
	close(fd);
	return (config);
}
