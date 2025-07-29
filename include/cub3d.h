/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggalle <anggalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:28:46 by paromero          #+#    #+#             */
/*   Updated: 2025/07/29 11:58:25 by anggalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <stdio.h>

/* ========================================================================= */
/* 📌 Vector entero 2D: para coordenadas de mapa, grillas, píxeles exactos */
/* ========================================================================= */
typedef struct s_vector2i {
	int x;
	int y;
} t_vector2i;

/* ========================================================================= */
/* 📌 Vector flotante 2D: para posición/movimiento en el espacio real */
/* ========================================================================= */
typedef struct s_vector2f {
	float x;
	float y;
} t_vector2f;

/* ========================================================================= */
/* 📌 Textura genérica de MLX: almacena imagen y metadatos */
/* ========================================================================= */
typedef struct s_texture {
	void *img;
	char *addr;
	int width;
	int height;
	int bpp;
	int line_len;
	int endian;
} t_texture;

/* ========================================================================= */
/* 📌 Jugador: posición, dirección y plano de cámara para raycasting */
/* ========================================================================= */
typedef struct s_player {
	t_vector2f pos;        // Posición actual (flotante, dentro del mapa)
	t_vector2f dir;        // Dirección hacia donde mira (unitario)
	t_vector2f plane;      // Plano de cámara (perpendicular a dir)
	float move_speed;      // Velocidad de movimiento
	float rot_speed;       // Velocidad de rotación
} t_player;

/* ========================================================================= */
/* 📌 Datos del mapa: grid y dimensiones */
/* ========================================================================= */
typedef struct s_map {
	char **grid;         // Matriz del mapa original
	int width;
	int height;
} t_map;

/* ========================================================================= */
/* 📌 Configuración general parseada desde .cub */
/* ========================================================================= */
typedef struct s_config {
	char *no_path;       // Textura pared norte
	char *so_path;       // Textura pared sur
	char *we_path;       // Textura pared oeste
	char *ea_path;       // Textura pared este
	int floor_color;     // Color del suelo
	int ceiling_color;   // Color del techo
	t_map map;          // Datos del mapa
	t_vector2f player_start;  // Posición inicial del jugador
	char player_dir;     // Dirección inicial: N, S, E, W
} t_config;

/* ========================================================================= */
/* 📌 Control general del motor y render: mlx, texturas, jugador */
/* ========================================================================= */
typedef struct s_game {
	void *mlx;
	void *win;

	t_config config;          // Configuración base parseada
	t_player player;          // Jugador activo
	t_texture textures[4];    // NO, SO, WE, EA orden: 0=N,1=S,2=W,3=E
} t_game;

#endif