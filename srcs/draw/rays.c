/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:46:48 by vvandenb          #+#    #+#             */
/*   Updated: 2022/06/01 09:49:43 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	draw_ray(t_data *data, t_ray *ray, size_t i)
{
	float		wall_offset;
	t_ray_s		ray_s;

	if (ray->hit_wall && ray->dist_to_player <= S_VIEW_DISTANCE)
	{
		ray_s.wall_height = SCREEN_HEIGHT
			/ (ray->dist_to_player * cos(data->player.angle - ray->angle));
		ray_s.text_step_y = (float)ray->texture->size.y / ray_s.wall_height;
		ray_s.t_pos.y = 0;
		if (ray_s.wall_height < 0 || ray_s.wall_height > SCREEN_HEIGHT)
		{
			ray_s.t_pos.y = ray_s.text_step_y
				* ((ray_s.wall_height - SCREEN_HEIGHT) / 2);
			ray_s.wall_height = SCREEN_HEIGHT;
		}
		if (ray->orientation == HORIZONTAL)
			wall_offset = ray->hit.x;
		else
			wall_offset = ray->hit.y;
		wall_offset -= floor((wall_offset));
		ray_s.t_pos.x = wall_offset * ray->texture->size.x;
		draw_wall(data, i, ray, &ray_s);
	}
	else
		draw_fog(i, data);
}

static t_ray	*set_ray(t_ray *ray_horiz, t_ray *ray_vert,
	t_texture *ts, t_fpoint *p_pos)
{
	t_ray	*ray;

	if (!ray_horiz->hit_wall)
		ray = ray_vert;
	else if (!ray_vert->hit_wall)
		ray = ray_horiz;
	else if (distance(p_pos, &ray_horiz->hit)
		< distance(p_pos, &ray_vert->hit))
		ray = ray_horiz;
	else
		ray = ray_vert;
	if (ray->orientation == HORIZONTAL && ray->angle > M_PI)
		ray->texture = ts + 1;
	else if (ray->orientation == HORIZONTAL)
		ray->texture = ts + 0;
	else if (ray->orientation == VERTICAL
		&& (ray->angle > M_PI / 2 && ray->angle < 3 * M_PI / 2))
		ray->texture = ts + 2;
	else
		ray->texture = ts + 3;
	if (ray->hit_wall)
		ray->dist_to_player = distance(p_pos, &ray->hit);
	return (ray);
}

void	draw_rays(t_data *data, t_map *map, t_player *player)
{
	t_ray	ray_horizontal;
	t_ray	ray_vertical;
	t_ray	*ray;
	size_t	i;
	float	angle;

	i = 0;
	angle = player->angle
		+ (data->s.angle_increment * (data->s.ray_amount / 2));
	fix_angle(&angle);
	while (i < data->s.ray_amount)
	{
		ray_horizontal = check_horizontal(map, &player->pos, angle);
		ray_vertical = check_vertical(map, player->pos, angle);
		ray = set_ray(&ray_horizontal, &ray_vertical, data->config.textures,
				&data->player.pos);
		draw_ray(data, ray, i);
		++i;
		angle -= data->s.angle_increment;
		fix_angle(&angle);
	}
}
