/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paromero <paromero@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:00:00 by anggalle          #+#    #+#             */
/*   Updated: 2025/10/09 09:11:28 by paromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	validate_extension(char *path, int len)
{
	if (len < 4 || ft_strncmp(path + len - 4, ".png", 4) != 0)
	{
		ft_putstr_fd("Error: Texture path must end with .png\n", 2);
		return (-1);
	}
	return (0);
}

//! All valid png starts with those specific bytes
static int	validate_png_signature(int fd)
{
	unsigned char	png_signature[8];
	unsigned char	expected[8];
	ssize_t			bytes_read;

	expected[0] = 0x89;
	expected[1] = 0x50;
	expected[2] = 0x4E;
	expected[3] = 0x47;
	expected[4] = 0x0D;
	expected[5] = 0x0A;
	expected[6] = 0x1A;
	expected[7] = 0x0A;
	bytes_read = read(fd, png_signature, 8);
	if (bytes_read != 8)
	{
		ft_putstr_fd("Error: PNG file is too small or empty\n", 2);
		return (-1);
	}
	if (ft_memcmp(png_signature, expected, 8) != 0)
	{
		ft_putstr_fd("Error: Invalid PNG file signature\n", 2);
		return (-1);
	}
	return (0);
}

static int	check_path_basic(char *path)
{
	int	len;

	if (!path || ft_strlen(path) == 0)
		return (-1);
	len = ft_strlen(path);
	if (validate_extension(path, len) == -1)
		return (-1);
	if (path[len - 1] == '/')
	{
		ft_putstr_fd("Error: Texture path is a directory\n", 2);
		return (-1);
	}
	return (0);
}

int	validate_path(char *path)
{
	int	fd;

	if (check_path_basic(path) == -1)
		return (-1);
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error: Cannot open texture file\n", 2);
		return (-1);
	}
	if (validate_png_signature(fd) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	validate_color_string(char *color_str)
{
	if (!color_str || ft_strlen(color_str) == 0)
		return (-1);
	return (0);
}
