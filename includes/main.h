/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:09:17 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/23 12:40:37 by vvandenb         ###   ########.fr       */
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

# define SCREEN_WIDTH			800
# define SCREEN_HEIGHT			500
# define GAME_WIDTH				600
# define TILE_SIZE				15
# define PLAYER_SIZE			5
# define PLAYER_TILE_RATIO		(((float)PLAYER_SIZE / TILE_SIZE))
# define PLAYER_SPEED			0.1f
# define PLAYER_ROTATE_SPEED	0.05f
# define MAX_RAY_LOOPS			10
# define MAX_KEYS_PRESSED		5
# define RAD1					0.0174532925f
# define FLOOR_A				255
# define FLOOR_R				128
# define FLOOR_G				128
# define FLOOR_B				128

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

//Structure representing the player
typedef struct s_player {
	t_fpoint	pos;
	t_fpoint	orientation;
	double		angle;
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
	t_player	player;
	t_mlx_data	mlx_data;
	t_keys		keys;
}	t_data;

//mlx/
//	mlx_utils.c
//Draws a pixel on an mlx img
void	imgPixelPut(t_img *img, int color, t_point pos);
//Draws a square on an mlx img
void	imgSquarePut(t_img *img, int color, t_point pos, t_point size);
//Returns an int representing a color
int		argb(unsigned char a, unsigned char r, unsigned char g, unsigned char b);
//	hooks.c
//Returns 1 if `keycode` is pressed
char	keyPressed(int keycode, t_keys *keys);
//Register key presses
int		keyPressHook(int keycode, t_keys *keys);
//Register key releases
int		keyReleaseHook(int keycode, t_keys *keys);

//utils.c
//Prints error with `perror(s)` and exits `exit(i)`
void	exitPerror(char *s, int i);
//Prints error on `STDERR` and exits `exit(i)`
void	exitError(char *s, int i);

//init.c
//Inits the `t_data` structure
void	initData(char *map_name, t_data *data);
//Sets up hooks and launches the main loop
void	initLoop(void *mlx_ptr, void *win_ptr, t_data *data);

//player.c
void	movePlayer(t_data *data, t_keys *keys);

//raycast.c
void	drawRays(t_mlx_data *mlx, t_map *map, t_player *player);

//draw.c
void	draw(t_data *data);

//main.c
int		mainLoop(t_data *data);

//REMOVE!
# include "debug.h"

#endif
