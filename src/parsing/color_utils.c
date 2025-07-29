/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggalle <anggalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:00:00 by anggalle          #+#    #+#             */
/*   Updated: 2025/07/29 14:13:22 by anggalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Safe atoi with range validation (0-255)
static int	ft_atoi_safe(char *str)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	// Skip leading spaces
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (result > 255)
		{
			ft_putstr_fd("Error: RGB value out of range (0-255)\n", 2);
			return (-1);
		}
		i++;
	}
	// Skip trailing spaces
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] != '\0')
	{
		ft_putstr_fd("Error: Invalid RGB format\n", 2);
		return (-1);
	}
	return (result);
}

// Extracts RGB values from "R,G,B" string
static int	extract_rgb_values(char *color_str, int *r, int *g, int *b)
{
	char	**parts;
	int		count;

	parts = ft_split(color_str, ',');
	if (!parts)
	{
		ft_putstr_fd("Error: Memory allocation failed\n", 2);
		return (-1);
	}
	count = 0;
	while (parts[count])
		count++;
	if (count != 3)
	{
		ft_putstr_fd("Error: RGB must have exactly 3 values (R,G,B)\n", 2);
		free_array(parts);
		return (-1);
	}
	*r = ft_atoi_safe(parts[0]);
	*g = ft_atoi_safe(parts[1]);
	*b = ft_atoi_safe(parts[2]);
	free_array(parts);
	if (*r == -1 || *g == -1 || *b == -1)
		return (-1);
	return (0);
}

// Parses RGB color string and returns integer color value
int	parse_rgb(char *color_str)
{
	int	r;
	int	g;
	int	b;

	if (!color_str)
	{
		ft_putstr_fd("Error: Empty color string\n", 2);
		return (-1);
	}
	if (extract_rgb_values(color_str, &r, &g, &b) == -1)
		return (-1);
	return ((r << 16) | (g << 8) | b);
}
