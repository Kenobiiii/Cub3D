/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggalle <anggalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:00:00 by anggalle          #+#    #+#             */
/*   Updated: 2025/07/29 12:25:24 by anggalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Convierte un string a entero con validación de rango (0-255)
static int	ft_atoi_safe(const char *str)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (result > 255)
			return (-1);
		i++;
	}
	return (result);
}

// Extrae los valores R, G, B de un string "R,G,B"
static int	extract_rgb_values(char *color_str, int *r, int *g, int *b)
{
	char	**parts;

	parts = ft_split(color_str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
	{
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

// Convierte un string RGB "R,G,B" a un entero de color
int	parse_rgb(char *color_str)
{
	int	r;
	int	g;
	int	b;

	if (!color_str)
		return (-1);
	if (extract_rgb_values(color_str, &r, &g, &b) == -1)
		return (-1);
	return ((r << 16) | (g << 8) | b);
}
