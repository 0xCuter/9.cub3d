/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:09:17 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/31 12:52:50 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "libft.h"
# include "get_next_line.h"
# include "utils.h"
# include "settings.h"
# include "keymap.h"
# include "mlx.h"
# include <X11/X.h>

//CONSTANTS
# define SPACES " \t\n\v\f\r"
# define SCREEN_WIDTH				800
# define SCREEN_HEIGHT				500
# define GAME_WIDTH					600
# define MAX_KEYS_PRESSED			5
# define RAD1						0.0174532925f

enum e_tiles {
	T_WALL = '1',
	T_EMPTY = '0'
};

enum e_ray_orientation {
	VERTICAL,
	HORIZONTAL
};

//Structure representing a cast ray
typedef struct s_ray_settings {
	float		text_step_y;
	int			wall_height;
	t_fpoint	t_pos;
}	t_ray_s;

//Structure representing a cast ray
typedef struct s_ray {
	char		hit_wall;
	t_fpoint	hit;
	float		angle;
	char		orientation;
	t_texture	*texture;
	float		dist_to_player;
}	t_ray;

//Structure representing the map
typedef struct s_map {
	char	*map;
	size_t	height;
	size_t	width;
}	t_map;

//Structure holding the map's config data
typedef struct s_config {
	t_texture	textures[4];
	int			color[2];
}	t_config;

//Structure representing the player
typedef struct s_player {
	t_fpoint	pos;
	t_fpoint	orientation;
	float		angle;
	float		vertical_angle;
}	t_player;

//Structure holding the mlx's data
typedef struct s_mlx_data {
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
}	t_mlx_data;

//Structure holding the pressed keys
typedef struct s_keys {
	int		keys[MAX_KEYS_PRESSED];
	size_t	keys_pressed_count;
}	t_keys;

//Structure holding the game's settings
typedef struct s_settings {
	char	shade;
	size_t	view_distance;
	size_t	fov;
	size_t	ray_amount;
	float	angle_increment;
}	t_settings;

//Structure holding the program's data
typedef struct s_data {
	t_map		map;
	t_settings	s;
	t_config	config;
	t_player	player;
	t_mlx_data	mlx_data;
	t_keys		keys;
}	t_data;

//mlx/
//	mlx_utils.c
//Draws a pixel on an mlx img
void	img_pixel_put(t_img *img, int color, t_point pos);
//Draws a square on an mlx img
void	img_square_put(t_img *img, int color, t_point pos, t_point size);
//Returns an int representing a color
int		argb(unsigned char a, unsigned char r,
			unsigned char g, unsigned char b);
//	hooks.c
//Returns 1 if `keycode` is pressed
char	key_pressed(int keycode, t_keys *keys);
//Register key presses
int		key_press_hook(int keycode, t_keys *keys);
//Register key releases
int		key_release_hook(int keycode, t_keys *keys);

//init/
//	init.c
//Inits the `t_data` structure
void	init_data(char *map_name, t_data *data);
//Exits if the file does not have the correct extension
void	check_ext(char *name, char *ext, int fd);
//Sets up hooks and launches the main loop
void	init_loop(void *mlx_ptr, void *win_ptr, t_data *data);

//	init_map.c
//Initializes the map data structure
void	init_map(t_data *data, char *line, int fd, char *map_name);

//	init_config.c
//Parses the config data structure
char	*parse_config(t_data *data, char *line, int fd);

//	parsing.c
//Parses the texture file path in the config data structure
void	parse_texture(char *line, int id, int fd, t_data *data);
//Parses the RGB color value in the config data structure
void	parse_color(char *line, int id, int fd, t_data *data);

//player.c
void	control_player(t_data *data, t_keys *keys);

//raycast.c
void	draw_rays(t_data *data, t_map *map, t_player *player);

//draw.c
void	draw(t_data *data);

//main.c
int		main_loop(t_data *data);

//REMOVE!
# include "debug.h"

#endif
