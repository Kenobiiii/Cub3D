/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggalle <anggalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:23:45 by anggalle          #+#    #+#             */
/*   Updated: 2025/07/29 14:29:01 by anggalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Checks if line is a texture identifier
int	is_texture_line(char *line)
{
	return ((line[0] == 'N' && line[1] == 'O')
		|| (line[0] == 'S' && line[1] == 'O')
		|| (line[0] == 'W' && line[1] == 'E')
		|| (line[0] == 'E' && line[1] == 'A'));
}

// Checks if line is a color identifier
int	is_color_line(char *line)
{
	return (line[0] == 'F' || line[0] == 'C');
}

// Validates and stores color value
int	store_color_value(char *line, int color, t_config *config)
{
	if (line[0] == 'F' && config->floor_color == -1)
		config->floor_color = color;
	else if (line[0] == 'C' && config->ceiling_color == -1)
		config->ceiling_color = color;
	else
	{
		ft_putstr_fd("Error: Duplicate or invalid color identifier\n", 2);
		return (-1);
	}
	return (0);
}

// Validates and stores texture path
int	store_texture_path(char *line, char *path, t_config *config)
{
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
		ft_putstr_fd("Error: Duplicate or invalid texture identifier\n",
			2);
		return (-1);
	}
	return (0);
}
