/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:31:13 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/16 11:42:51 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	img_pixel_put(t_img *img, int color, t_point pos)
{
	char	*dst;

	if (pos.y >= 0 && pos.x >= 0
		&& pos.y < SCREEN_HEIGHT && pos.x < img->line_len / (img->bits_per_pixel / 8))
	{
		dst = img->addr + (pos.y * img->line_len + pos.x * (img->bits_per_pixel / 8));
		*(int *)dst = color;
	}
}

void	img_square_put(t_img *img, int color, t_point pos, t_point size)
{
	int	x;

	while (size.y)
	{
		x = size.x;
		while (x)
		{
			img_pixel_put(img, color,
				(t_point){pos.x + x - 1, pos.y + size.y - 1});
			--x;
		}
		--size.y;
	}
}

//Called when pressing window close
static int	exit_program()
{
	exit(0);
}

void	init_loop(void *mlx_ptr, void *win_ptr, t_data *data)
{
	// t_mouse_hook	mouse_params;
	// t_key_hook		key_params;

	// mouse_params = (t_mouse_hook){mlx_ptr, win_ptr};
	mlx_mouse_hook(win_ptr, mouse_hook, NULL);
	// key_params = (t_key_hook){mlx_ptr, win_ptr};
	mlx_hook(win_ptr, 2, 1L << 0, key_press_hook, data);
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
