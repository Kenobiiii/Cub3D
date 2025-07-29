/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggalle <anggalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:28:46 by paromero          #+#    #+#             */
/*   Updated: 2025/07/29 14:17:27 by anggalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <stdio.h>
# include <fcntl.h>

/* ========================================================================= */
/* 📌 Vector entero 2D: para coordenadas de mapa, grillas, píxeles exactos */
/* ========================================================================= */
typedef struct s_vector2i
{
	int	x;
	int	y;
}	t_vector2i;

/* ========================================================================= */
/* 📌 Vector flotante 2D: para posición/movimiento en el espacio real */
/* ========================================================================= */
typedef struct s_vector2f
{
	float	x;
	float	y;
}	t_vector2f;

/* ========================================================================= */
/* 📌 Textura genérica de MLX: almacena imagen y metadatos */
/* ========================================================================= */
typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

/* ========================================================================= */
/* 📌 Jugador: posición, dirección y plano de cámara para raycasting */
/* ========================================================================= */
typedef struct s_player
{
	t_vector2f	pos;
	t_vector2f	dir;
	t_vector2f	plane;
	float		move_speed;
	float		rot_speed;
}	t_player;

/* ========================================================================= */
/* 📌 Datos del mapa: grid y dimensiones */
/* ========================================================================= */
typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

/* ========================================================================= */
/* 📌 Configuración general parseada desde .cub */
/* ========================================================================= */
typedef struct s_config
{
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	int			floor_color;
	int			ceiling_color;
	char		*map_path;
	t_map		map;
	t_vector2f	player_start;
	char		player_dir;
}	t_config;

/* ========================================================================= */
/* 📌 Control general del motor y render: mlx, texturas, jugador */
/* ========================================================================= */
typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_config	config;
	t_player	player;
	t_texture	textures[4];
}	t_game;

/* ========================================================================= */
/* 📌 Funciones de parsing */
/* ========================================================================= */

// Función principal de parsing
t_config	parse_file(char *filename);

// Lectura de elementos de configuración
int			read_config_elements(int fd, t_config *config);

// Lectura del mapa
int			read_map(int fd, t_config *config);

// Validación del mapa
int			validate_map(t_config *config);
int			validate_walls(t_config *config);
int			validate_player(t_config *config);

// Utilidades de color
int			parse_rgb(char *color_str);

// Utilidades de memoria
void		free_array(char **array);

// wall_utils.c
int			validate_extra_chars(int i, int start, int len, t_config *config);
int			validate_length_rules(int i, int len, t_config *config);
int			find_first_char(int i, int len, t_config *config);
int			find_last_char(int i, int len, t_config *config);
int			validate_internal_spaces(int i, int len, t_config *config);

// config_utils.c
int			validate_path(char *path);
int			validate_color_string(char *color_str);

#endif