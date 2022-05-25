/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:31:13 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/25 16:46:01 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	img_pixel_put(t_img *img, int color, t_point pos)
{
	char	*dst;

	if (pos.y >= 0 && pos.x >= 0 && pos.y < SCREEN_HEIGHT
		&& pos.x < img->line_len / (img->bits_per_pixel / 8))
	{
		dst = img->addr
			+ pos.y * img->line_len + pos.x * (img->bits_per_pixel / 8);
		*(int *)dst = color;
	}
}

void	img_square_put(t_img *img, int color, t_point pos, t_point size)
{
	int	x;

	while (size.y > 0)
	{
		x = size.x;
		while (x > 0)
		{
			img_pixel_put(img, color,
				(t_point){pos.x + x - 1, pos.y + size.y - 1});
			--x;
		}
		--size.y;
	}
}

int	argb(unsigned char a, unsigned char r, unsigned char g, unsigned char b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}
