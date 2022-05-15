/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:09:17 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/16 00:33:13 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <fcntl.h>
# include "libft.h"
# include "get_next_line.h"
# include "keymap.h"
# include "mlx.h"

# define SCREEN_WIDTH	500
# define SCREEN_HEIGHT	500

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_mouse_hook {
	void			*mlx_ptr;
	void			*win_ptr;
}	t_mouse_hook;

typedef struct s_key_hook {
	void			*mlx_ptr;
	void			*win_ptr;
}	t_key_hook;

typedef struct s_map {
	void	*mlx_ptr;
	void	*win_ptr;

	char	*map;
	t_img	img;
	size_t	len;
}	t_map;

//mlx_utils.c
// Put color in image
void	img_pixel_put(t_img *img, int x, int y, int color);
// Sets up keyboard and mouse hooks, then launches main loop
void	init_loop(void *mlx_ptr, void *win_ptr, t_map *map);
// Returns an int representing a color
int		rgb(unsigned char r, unsigned char g, unsigned char b);

//hooks.c
int	mouse_hook(int button, int x, int y, void *param);
int	key_press_hook(int keycode, t_map *map);

//main.c
void	draw_map(t_map *map);

//debug/
# include "debug.h"

#endif
