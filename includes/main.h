/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:09:17 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/17 12:08:57 by vvandenb         ###   ########.fr       */
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

# define SCREEN_WIDTH			500
# define SCREEN_HEIGHT			500
# define TILE_SIZE				10
# define PLAYER_SIZE			15
# define PLAYER_SPEED			0.2
# define PLAYER_ROTATE_SPEED	0.1
# define MAX_KEYS_PRESSED		5

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
	size_t	len;
}	t_map;

//Structure representing the player
typedef struct s_player {
	t_fpoint	pos;
	t_fpoint	orientation;
	float		angle;
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
void	img_pixel_put(t_img *img, int color, t_point pos);
//Draws a square on an mlx img
void	img_square_put(t_img *img, int color, t_point pos, t_point size);
//Returns an int representing a color
int		rgb(unsigned char r, unsigned char g, unsigned char b);
//	hooks.c
//Returns 1 if `keycode` is pressed
char	key_pressed(int keycode, t_keys *keys);
//Register key presses
int		key_press_hook(int keycode, t_keys *keys);
//Register key releases
int		key_release_hook(int keycode, t_keys *keys);

//utils.c
//Prints error with `perror(s)` and exits `exit(i)`
void	exit_perror(char *s, int i);
//Prints error on `STDERR` and exits `exit(i)`
void	exit_error(char *s, int i);

//init.c
//Inits the `t_data` structure
void	init_data(char *map_name, t_data *data);
//Sets up hooks and launches the main loop
void	init_loop(void *mlx_ptr, void *win_ptr, t_data *data);

//player.c
void	move_player(t_data *data, t_keys *keys);

//main.c
void	draw(t_mlx_data *mlx_data, t_map *map, t_player *player);
int		main_loop(t_data *data);

//REMOVE!
# include "debug.h"

#endif
