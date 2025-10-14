/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 09:46:05 by paromero          #+#    #+#             */
/*   Updated: 2025/10/14 18:40:51 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "../MLX/include/MLX42/MLX42.h"

//! Windows config
# define WINDOW_WIDTH           1200
# define WINDOW_HEIGHT          1000
# define WINDOW_TITLE           "CUB3D"

//! Player confog
# define PLAYER_MOVE_SPEED      0.05f
# define PLAYER_ROT_SPEED       0.03f

//! Int vector 2D: for maps, pixel, coords
typedef struct s_vector2i
{
	int	x;
	int	y;
}	t_vector2i;

//! float vector for movement
typedef struct s_vector2f
{
	float	x;
	float	y;
}	t_vector2f;

typedef struct s_texture
{
	mlx_image_t	*img;
	int			width;
	int			height;
}	t_texture;

typedef struct s_texture_params
{
	t_texture	*texture;
	int			tex_x;
	int			tex_y;
}	t_texture_params;

typedef struct s_ray
{
	t_vector2f	pos;			//! actual position of the ray
	t_vector2f	dir;			//! direction
	t_vector2f	delta_dist;		//! distance in the grid
	t_vector2f	side_dist;		//! distance to the next grid
	t_vector2i	map_pos;		//! Pos in the map
	t_vector2i	step;			//! direction to the next grid
	float		perp_wall_dist;	//! distance to the wall
	float		camera_x;		//! Pos of the camera
	int			side;			//! side of the wall
	int			hit;			//! 1 = yes 0 = no
	int			tex_num;		//! Num of texture
	float		wall_x;			//! Pos where ray hit
	int			draw_start;		//! When did start
	int			draw_end;		//! When did end
}	t_ray;

typedef struct s_input
{
	int	w;
	int	s;
	int	a;
	int	d;
	int	left;
	int	right;
	int	esc;
}	t_input;

typedef struct s_player
{
	t_vector2f	pos;
	t_vector2f	dir;
	t_vector2f	fov;
	float		move_speed;
	float		rot_speed;
}	t_player;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

//! Map info
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

//! game struct
typedef struct s_game
{
	mlx_t		*mlx;
	t_texture	screen;
	t_config	config;
	t_player	player;
	t_texture	textures[4];
	t_ray		ray;
	t_input		input;
	int			win_width;
	int			win_height;	
}	t_game;

//DONE Parsing functions

//! Main parse function
t_config	parse_file(char *filename);

//! Reading of config
int			read_config_elements(int fd, t_config *config);

//! Map parse
int			read_map(int fd, t_config *config);

//! Map validation
int			validate_map(t_config *config);
int			validate_walls(t_config *config);
int			validate_player(t_config *config);

//! Color utilities
int			parse_rgb(char *color_str);

//! Memory utilities
void		free_array(char **array);
void		free_config(t_config *config);

//! Wall_utils
int			validate_extra_chars(int i, int start, int len, t_config *config);
int			validate_length_rules(int i, int len, t_config *config);
int			find_first_char(int i, int len, t_config *config);
int			find_last_char(int i, int len, t_config *config);
int			validate_internal_spaces(int i, int len, t_config *config);

//! Wall_helpers
int			flood_fill_check(t_config *config, int i, int j, char **visited);
int			init_visited_array(t_config *config, char **visited);
void		free_visited_array(char **visited, int height);
int			check_border_char(char c, int *result);
int			validate_walls_loop(t_config *config, char **visited);

//! Config_utils
int			validate_path(char *path);
int			validate_color_string(char *color_str);

//! Config_helpers
int			is_texture_line(char *line);
int			is_color_line(char *line);
int			store_color_value(char *line, int color, t_config *config);
int			store_texture_path(char *line, char *path, t_config *config);

//DONE Engine functions

//! mlx_init.c
int			init_mlx42(t_game *game);
int			close_game(t_game *game);

//! event_system.c
void		handle_keypress(mlx_key_data_t keydata, void *param);
void		handle_close(void *param);
void		game_update(void *param);

//! texture_init.c
int			load_textures(t_game *game);
void		cleanup_textures(t_game *game);

//! Player_init.c
void		init_player(t_game *game);

//! Render_background.c
void		render_background(t_game *game);

//! Input_system.c
void		update_input(t_game *game);

//! Collision_system.c
void		move_player(t_game *game, float new_x, float new_y);

//! render_basic.c
int			get_pixel(mlx_image_t *img, int x, int y);
int			create_rgba(int r, int g, int b, int a);

//! Raycasting_engine.c
int			raycasting_engine(t_game *game);

//! ray_dda.c
void		set_dda_params(t_ray *ray, t_game *game);
void		perform_dda_algorithm(t_game *game, t_ray *ray);
void		calculate_line_height(t_ray *ray, t_game *game);

//! Wall_rendering.c
void		draw_texture_column(t_game *game, t_ray *ray, int x, int tex_x);
int			calculate_tex_x(t_game *game, t_ray *ray);

#endif