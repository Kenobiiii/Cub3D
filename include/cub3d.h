/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paromero <paromero@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:28:46 by paromero          #+#    #+#             */
/*   Updated: 2025/07/29 10:02:38 by paromero         ###   ########.fr       */
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
/* 📌 Celda del mapa extendido (si usas estructura por celda en bonus) */
/* ========================================================================= */
typedef enum e_cell_type {
	CELL_EMPTY,
	CELL_WALL,
	CELL_DOOR_CLOSED,
	CELL_DOOR_OPEN
} t_cell_type;

/* ========================================================================= */
/* 📌 Puerta interactiva: estado, dirección y animación */
/* ========================================================================= */
typedef struct s_door {
	t_vector2i pos;       // Posición en el grid
	int is_open;          // Estado lógico
	float anim_state;     // Progreso de la animación (0.0 → 1.0)
	int direction;        // 0 = vertical, 1 = horizontal
} t_door;

/* ========================================================================= */
/* 📌 Lista de puertas: para control dinámico de múltiples instancias */
/* ========================================================================= */
typedef struct s_door_list {
	t_door door;
	struct s_door_list *next;
} t_door_list;

/* ========================================================================= */
/* 📌 Datos del mapa original: grid, dimensiones y parsing info */
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
	char *no_path;
	char *so_path;
	char *we_path;
	char *ea_path;
	int floor_color;
	int ceiling_color;
	t_map map;
	t_vector2f player_start;
	char player_dir;       // N, S, E, W
} t_config;

/* ========================================================================= */
/* 📌 Control general del motor y render: mlx, texturas, jugador, puertas */
/* ========================================================================= */
typedef struct s_game {
	void *mlx;
	void *win;

	t_config config;          // Configuración base parseada
	t_player player;          // Jugador activo
	t_texture textures[4];    // NO, SO, WE, EA orden: 0=N,1=S,2=W,3=E

	t_texture door_texture;   // Textura para puertas
	t_texture hud;            // HUD o interfaz opcional

	t_door_list *doors;       // Lista dinámica de puertas
} t_game;


#endif