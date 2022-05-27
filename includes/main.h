/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:09:17 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/27 10:31:27 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "libft.h"
# include "get_next_line.h"
# include "keymap.h"
# include "mlx.h"
# include <X11/X.h>

# define SPACES " \t\n\v\f\r"

# define SCREEN_WIDTH			800
# define SCREEN_HEIGHT			500
# define GAME_WIDTH				600
# define TILE_SIZE				15
# define PLAYER_SIZE			2
# define PLAYER_SPEED			0.1f
# define PLAYER_VERTICAL_SPEED	0.05f
# define PLAYER_ROTATE_SPEED	0.05f
# define MAX_KEYS_PRESSED		5
# define RAD1					0.0174532925f

//COLORS
// # define CEILING_R				113
// # define CEILING_G				205
// # define CEILING_B				241
// # define FLOOR_R				72
// # define FLOOR_G				111
// # define FLOOR_B				56

//SETTINGS
# define S_FOV					60
# define S_VIEW_DISTANCE		8

enum e_tiles {
	T_WALL = '1',
	T_EMPTY = '0'
};

//Structure representing a point with ints
typedef struct s_point {
	int	x;
	int	y;
}	t_point;

//Structure representing a point with floats
typedef struct s_fpoint {
	float	x;
	float	y;
}	t_fpoint;

//Structure representing an mlx image
typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}	t_img;

//Structure representing the map
typedef struct s_map {
	char	*map;
	size_t	height;
	size_t	width;
}	t_map;

typedef struct s_config {
	char	*texture[4];
	int		color[2];
}	t_config;

//Structure representing the player
typedef struct s_player {
	t_fpoint	pos;
	t_fpoint	orientation;
	double		angle;
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

//Structure holding the program's data
typedef struct s_data {
	t_map		map;
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
int		argb(unsigned char a, unsigned char r, unsigned char g, unsigned char b);
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

//utils_exit.c
//Prints error with `perror(s)` and exits `exit(i)`
void	exit_perror(char *s, int i);
//Prints error on `STDERR` and exits `exit(i)`
void	exit_error(char *s, int i);
//Same as `exit_error()` but also closes `fd`
void	exit_close_error(char *s, int i, int fd);

//utils.c
//"Fixes" an angle greater than 2PI or less than 0
void	fix_angle(double *angle);
//Same as `open()`, but exits on error
int		safe_open(char *file_name, int flags);
//Same as `close()`, but exits on error
void	safe_close(int fd);
//Checks if a string is all spaces
int		str_isspace(char *str);
//Frees a two-dimensional array
void	free_tab(char **tab);

//player.c
void	control_player(t_data *data, t_keys *keys);

//raycast.c
void	draw_rays(t_mlx_data *mlx, t_map *map, t_player *player);

//draw.c
void	draw(t_data *data);

//main.c
int		main_loop(t_data *data);

//REMOVE!
# include "debug.h"

#endif
