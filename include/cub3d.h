/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paromero <paromero@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:28:46 by paromero          #+#    #+#             */
/*   Updated: 2025/08/24 20:31:03 by paromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <stdio.h>
# include <fcntl.h>
# include "../MLX/include/MLX42/MLX42.h"

/* ========================================================================= */
/* 📌 Vector entero 2D: para coordenadas de mapa, grillas, píxeles exactos */
/* ========================================================================= */
typedef struct s_vector2i
{
    int x;
    int y;
}   t_vector2i;

/* ========================================================================= */
/* 📌 Vector flotante 2D: para posición/movimiento en el espacio real */
/* ========================================================================= */
typedef struct s_vector2f
{
    float   x;
    float   y;
}   t_vector2f;

/* ========================================================================= */
/* 📌 Textura genérica de MLX: almacena imagen y metadatos */
/* ========================================================================= */
typedef struct s_texture
{
    mlx_image_t    *img;
    int     width;
    int     height;
}   t_texture;

/* ========================================================================= */
/* 📌 Parámetros de textura: para funciones con múltiples argumentos */
/* ========================================================================= */
typedef struct s_texture_params
{
    t_texture   *texture;
    int         tex_x;
    int         tex_y;
}   t_texture_params;

/* ========================================================================= */
/* 📌 Rayo para raycasting: información completa del algoritmo DDA */
/* ========================================================================= */
typedef struct s_ray
{
    t_vector2f  pos;            // Posición actual del rayo
    t_vector2f  dir;            // Dirección del rayo
    t_vector2f  delta_dist;     // Distancia entre intersecciones X e Y
    t_vector2f  side_dist;      // Distancia a próxima intersección X e Y
    t_vector2i  map_pos;        // Posición actual en el mapa (grid)
    t_vector2i  step;           // Dirección de paso (+1 o -1) para X e Y
    float       perp_wall_dist; // Distancia perpendicular a la pared
    float       camera_x;       // Posición en el plano de cámara (-1 a 1)
    int         side;           // ¿Lado NS (0) o EW (1) de la pared?
    int         hit;            // ¿Golpeamos una pared? (0=no, 1=sí)
    int         tex_num;        // Número de textura a usar (0=NO, 1=SO, 2=WE, 3=EA)
    float       wall_x;         // Posición exacta donde el rayo golpea la pared
    int         draw_start;     // Píxel Y donde empezar a dibujar
    int         draw_end;       // Píxel Y donde terminar de dibujar
}   t_ray;

/* ========================================================================= */
/* 📌 Input del jugador: estado de todas las teclas */
/* ========================================================================= */
typedef struct s_input
{
    int w;          // Avanzar
    int s;          // Retroceder
    int a;          // Izquierda (strafe)
    int d;          // Derecha (strafe)
    int left;       // Rotar izquierda
    int right;      // Rotar derecha
    int esc;        // Salir
}   t_input;

/* ========================================================================= */
/* 📌 Jugador: posición, dirección y plano de cámara para raycasting */
/* ========================================================================= */
typedef struct s_player
{
    t_vector2f  pos;            // Posición actual en el mundo
    t_vector2f  dir;            // Vector dirección (hacia donde mira)
    t_vector2f  fov;            // Campo de visión (field of view)
    float       move_speed;     // Velocidad de movimiento
    float       rot_speed;      // Velocidad de rotación
}   t_player;

/* ========================================================================= */
/* 📌 Datos del mapa: grid y dimensiones */
/* ========================================================================= */
typedef struct s_map
{
    char    **grid;     // Matriz 2D del mapa
    int     width;      // Ancho en caracteres
    int     height;     // Alto en líneas
}   t_map;

/* ========================================================================= */
/* 📌 Configuración general parseada desde .cub */
/* ========================================================================= */
typedef struct s_config
{
    char        *no_path;       // Ruta textura Norte
    char        *so_path;       // Ruta textura Sur
    char        *we_path;       // Ruta textura Oeste
    char        *ea_path;       // Ruta textura Este
    int         floor_color;    // Color suelo (RGB)
    int         ceiling_color;  // Color techo (RGB)
    char        *map_path;      // Ruta del archivo .cub
    t_map       map;            // Datos del mapa
    t_vector2f  player_start;   // Posición inicial del jugador
    char        player_dir;     // Dirección inicial ('N', 'S', 'E', 'W')
}   t_config;

/* ========================================================================= */
/* 📌 Control general del motor y render: mlx, texturas, jugador */
/* ========================================================================= */
typedef struct s_game
{
    mlx_t        *mlx;           // Puntero MLX
    t_texture   screen;         // Buffer de pantalla para renderizar
    t_config    config;         // Configuración parseada
    t_player    player;         // Estado del jugador
    t_texture   textures[4];    // Texturas cargadas [NO, SO, WE, EA]
    t_ray       ray;            // Rayo actual para raycasting
    t_input     input;          // Estado del input
    int         win_width;      // Ancho de ventana
    int         win_height;     // Alto de ventana
}   t_game;

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

// config_helpers.c
int			is_texture_line(char *line);
int			is_color_line(char *line);
int			store_color_value(char *line, int color, t_config *config);
int			store_texture_path(char *line, char *path, t_config *config);

/* ========================================================================= */
/* 📌 Funciones MLX42 personalizadas */
/* ========================================================================= */

// Inicialización y cierre
int			init_mlx42(t_game *game);
int			close_game(t_game *game);

// Manipulación de píxeles
void		put_pixel(mlx_image_t *img, int x, int y, int color);
int			get_pixel(mlx_image_t *img, int x, int y);
int			create_rgba(int r, int g, int b, int a);

// Renderizado básico
void		clear_screen(mlx_image_t *img);
void		draw_floor_ceiling(mlx_image_t *img, int floor_color, int ceiling_color);
void		put_texture_pixel(t_game *game, int x, int y, t_texture_params *params);
void		draw_texture_column(t_game *game, t_ray *ray, int x, int tex_x);
void		draw_texture_loop(t_game *game, t_ray *ray, int x, int tex_x);

// Renderizado principal
void		render_background(t_game *game);
void		render_frame(t_game *game);

// Game loop y eventos
void		handle_keypress(mlx_key_data_t keydata, void *param);
void		handle_close(void *param);

// Carga de texturas
int			load_textures(t_game *game);
int			load_single_texture(t_game *game, char *path, int index);
void		cleanup_textures(t_game *game);

// Inicialización del jugador
void		init_player(t_game *game);
void		set_direction_vectors(t_player *player, char direction);
int			validate_player_position(t_game *game);

// Sistema de input y movimiento
void		update_input(t_game *game);
void		update_player_movement(t_game *game);
void		update_player_rotation(t_game *game);
void		rotate_vectors(t_vector2f *dir, t_vector2f *fov, float angle);
void		game_update(void *param);

// Collision detection
int			is_valid_position(t_game *game, float x, float y);
void		move_player_safe(t_game *game, float new_x, float new_y);

// Raycasting y DDA
void		init_ray(t_ray *ray, t_game *game, int x);
void		calculate_delta_dist(t_ray *ray);
void		calculate_step_and_side_dist(t_ray *ray);
void		perform_dda(t_ray *ray, t_game *game);
void		calculate_wall_distance(t_ray *ray);
void		determine_wall_texture(t_ray *ray);
void		cast_single_ray(t_ray *ray, t_game *game, int x);
int			raycasting_engine(t_game *game);
void		init_ray_data(t_ray *ray);

// Renderizado de paredes
void		calculate_wall_x(t_ray *ray);
void		calculate_draw_limits(t_ray *ray, t_game *game, int *draw_start, 
				int *draw_end);
void		draw_wall_column(t_game *game, t_ray *ray, int x);

/* ========================================================================= */
/* 📌 Constantes configurables del juego */
/* ========================================================================= */

// Configuración de ventana
# define WINDOW_WIDTH           800
# define WINDOW_HEIGHT          600
# define WINDOW_TITLE           "CUB3D"

// Configuración del jugador
# define PLAYER_MOVE_SPEED      0.05f
# define PLAYER_ROT_SPEED       0.03f

#endif