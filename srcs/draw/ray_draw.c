/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:26:21 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/31 14:27:25 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	find_color(t_ray *ray, t_fpoint *t_pos, char *b_shade, t_texture *t)
{
	int	color;

	if (ray->orientation == HORIZONTAL)
	{
		if (ray->angle > M_PI)
			color = ((int *)t->img.addr)
			[(int)(t->size.x - t_pos->x) + t->size.y * (int)t_pos->y];
		else
			color = ((int *)t->img.addr)
			[(int)t_pos->x + t->size.y * (int)t_pos->y];
	}
	else
	{
		if (ray->angle > M_PI / 2 && ray->angle < 3 * M_PI / 2)
			color = ((int *)t->img.addr)
			[(int)(t->size.x - t_pos->x) + t->size.y * (int)t_pos->y];
		else
			color = ((int *)t->img.addr)
			[(int)t_pos->x + t->size.y * (int)t_pos->y];
	}
	if (*b_shade && ray->orientation == VERTICAL)
		color = (color >> 1) & 8355711;
	return (color);
}

void	draw_wall(t_data *data, int i, t_ray *ray, t_ray_s *ray_s)
{
	int	y;
	int	draw_height;

	y = (SCREEN_HEIGHT - ray_s->wall_height) * data->player.vertical_angle;
	draw_height = y + ray_s->wall_height;
	while (y < draw_height)
	{
		img_square_put(&data->mlx_data.img,
			find_color(ray, &ray_s->t_pos, &data->s.shade, ray->texture),
			(t_point){((float)GAME_WIDTH / data->s.ray_amount) * i, y},
			(t_point){((float)GAME_WIDTH / data->s.ray_amount) + 1, 1});
		ray_s->t_pos.y += ray_s->text_step_y;
		++y;
	}
}

void	draw_fog(int i, t_data *data, float *vertical_angle)
{
	img_square_put(&data->mlx_data.img, argb(0, 0, 0, 0),
		(t_point){i * ((float)GAME_WIDTH / data->s.ray_amount),
		(SCREEN_HEIGHT - (SCREEN_HEIGHT / S_VIEW_DISTANCE)) * *vertical_angle},
		(t_point){((float)GAME_WIDTH / data->s.ray_amount) + 1,
		SCREEN_HEIGHT / S_VIEW_DISTANCE});
}
