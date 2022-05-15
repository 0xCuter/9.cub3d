/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:31:13 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/16 00:01:18 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	img_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (y >= 0 && x >= 0
		&& y < SCREEN_HEIGHT && x < img->line_len / (img->bits_per_pixel / 8))
	{
		dst = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
		*(int *)dst = color;
		// printf("COLORD: x: %i y: %i\n", y * img->line_len + x * (img->bits_per_pixel / 8) );
	}
}

static int	exit_program()
{
	exit(0);
}

void	init_loop(void *mlx_ptr, void *win_ptr, t_map *map)
{
	// t_mouse_hook	mouse_params;
	// t_key_hook		key_params;

	// mouse_params = (t_mouse_hook){mlx_ptr, win_ptr};
	mlx_mouse_hook(win_ptr, mouse_hook, NULL);
	// key_params = (t_key_hook){mlx_ptr, win_ptr};
	mlx_hook(win_ptr, 2, 1L << 0, key_press_hook, map);
	mlx_hook(win_ptr, 17, 0, exit_program, NULL);
	mlx_loop(mlx_ptr);
}

int	rgb(unsigned char r, unsigned char g, unsigned char b)
{
	int	color;

	color = 0;
	color |= r;
	color <<= 8;
	color |= g;
	color <<= 8;
	color |= b;
	return (color);
}
