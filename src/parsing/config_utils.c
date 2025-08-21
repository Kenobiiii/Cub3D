/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paromero <paromero@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:00:00 by anggalle          #+#    #+#             */
/*   Updated: 2025/08/21 18:51:08 by paromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <sys/stat.h>

int	validate_path(char *path)
{
	struct stat	path_stat;
	int		len;

	if (!path || ft_strlen(path) == 0)
		return (-1);
	len = ft_strlen(path);
	if (len < 4 || (ft_strncmp(path + len - 4, ".xpm", 4) != 0 
		&& ft_strncmp(path + len - 4, ".png", 4) != 0))
	{
		ft_putstr_fd("Error: Texture path must end with .xpm or .png\n", 2);
		return (-1);
	}
	if (path[ft_strlen(path) - 1] == '/')
	{
		ft_putstr_fd("Error: Texture path is a directory\n", 2);
		return (-1);
	}
	if (stat(path, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			ft_putstr_fd("Error: Texture path is a directory\n", 2);
			return (-1);
		}
		if (!S_ISREG(path_stat.st_mode))
		{
			ft_putstr_fd("Error: Texture path is not a regular file\n", 2);
			return (-1);
		}
	}
	return (0);
}

int	validate_color_string(char *color_str)
{
	if (!color_str || ft_strlen(color_str) == 0)
		return (-1);
	return (0);
}
