/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggalle <anggalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:15:50 by anggalle          #+#    #+#             */
/*   Updated: 2025/07/29 13:58:32 by anggalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_extra_chars(int i, int start, int len, t_config *config)
{
	int	j;

	j = start;
	while (j < len)
	{
		if (config->map.grid[i][j] != '1')
			return (-1);
		j++;
	}
	return (0);
}

int	validate_length_rules(int i, int len, t_config *config)
{
	int	top_len;
	int	bottom_len;

	top_len = 0;
	bottom_len = 0;
	if (i > 0)
		top_len = ft_strlen(config->map.grid[i - 1]);
	if (i + 1 < config->map.height)
		bottom_len = ft_strlen(config->map.grid[i + 1]);
	if (len > top_len)
	{
		if (validate_extra_chars(i, top_len, len, config) == -1)
			return (-1);
	}
	if (len > bottom_len)
	{
		if (validate_extra_chars(i, bottom_len, len, config) == -1)
			return (-1);
	}
	return (0);
}

int	find_first_char(int i, int len, t_config *config)
{
	int	j;

	j = 0;
	while (j < len && config->map.grid[i][j] == ' ')
		j++;
	if (j < len)
		return (config->map.grid[i][j]);
	return (0);
}

int	find_last_char(int i, int len, t_config *config)
{
	int	j;

	j = len - 1;
	while (j >= 0 && config->map.grid[i][j] == ' ')
		j--;
	if (j >= 0)
		return (config->map.grid[i][j]);
	return (0);
}

int	validate_internal_spaces(int i, int len, t_config *config)
{
	int	j;

	j = 0;
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
