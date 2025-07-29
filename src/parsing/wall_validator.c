/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_validator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggalle <anggalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:00:00 by anggalle          #+#    #+#             */
/*   Updated: 2025/07/29 13:17:48 by anggalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	validate_boundary_rows(int i, int j, int len, t_config *config)
{
	while (j < len)
	{
		if (config->map.grid[i][j] != '1' && config->map.grid[i][j] != ' ')
			return (-1);
		j++;
	}
	return (0);
}

static int	validate_internal_rows(int i, int j, int len, t_config *config)
{
	if (j < len && config->map.grid[i][j] != '1')
		return (-1);
	if (len > 0 && config->map.grid[i][len - 1] != '1')
		return (-1);
	while (j < len)
	{
		if (config->map.grid[i][j] == ' ')
		{
			if (j > 0 && config->map.grid[i][j - 1] != '1'
				&& config->map.grid[i][j - 1] != ' ')
				return (-1);
			if (j + 1 < len && config->map.grid[i][j + 1] != '1'
				&& config->map.grid[i][j + 1] != ' ')
				return (-1);
		}
		j++;
	}
	return (0);
}

static int	validate_row(int i, t_config *config)
{
	int	j;
	int	len;

	j = 0;
	len = ft_strlen(config->map.grid[i]);
	while (j < len && config->map.grid[i][j] == ' ')
		j++;
	if (i == 0 || i == config->map.height - 1)
	{
		if (validate_boundary_rows(i, j, len, config) == -1)
			return (-1);
	}
	else
	{
		if (validate_internal_rows(i, j, len, config) == -1)
			return (-1);
	}
	if (validate_length_rules(i, len, config) == -1)
		return (-1);
	return (0);
}

int	validate_walls(t_config *config)
{
	int	i;

	i = 0;
	while (i < config->map.height)
	{
		if (validate_row(i, config) == -1)
			return (-1);
		i++;
	}
	return (0);
}
