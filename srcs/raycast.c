/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:46:48 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/31 12:55:29 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static float	distance(t_fpoint *p1, t_fpoint *p2)
{
	return (sqrt((p1->y - p2->y) * (p1->y - p2->y)
			+ (p1->x - p2->x) * (p1->x - p2->x)));
}

static t_fpoint	setup_check(t_fpoint *offset, t_fpoint p_pos, char b, float a)
{
	t_fpoint	ray;

	ray.y = (int)p_pos.y;
	if (b)
		offset->y = -1;
	else
		offset->y = 1;
	if (offset->y == 1)
		ray.y += 1;
	ray.x = (p_pos.y - ray.y) * a + p_pos.x;
	offset->x = -offset->y * a;
	return (ray);
}

static t_ray	check_horizontal(t_map *map, t_fpoint *p_pos, float angle)
{
	t_fpoint	ray;
	t_fpoint	offset;
	int			tile;

	if (angle == M_PI || angle == 0)
		return ((t_ray){0, (t_fpoint){0, 0}, angle, HORIZONTAL, NULL, 0});
	ray = setup_check(&offset, *p_pos, angle < M_PI, 1 / tan(angle));
	while (distance(p_pos, &ray) <= S_VIEW_DISTANCE)
	{
		if (ray.x < 0 || ray.y < 0 || (offset.y == -1 && ray.y - 1 < 0))
			return ((t_ray){0, (t_fpoint){0, 0}, angle, HORIZONTAL, NULL, 0});
		if (offset.y == -1)
			tile = (int)ray.x + (int)(ray.y - 1) * map->width;
		else
			tile = (int)ray.x + (int)ray.y * map->width;
		if (tile >= 0 && tile < (int)(map->width * map->height)
			&& map->map[tile] == T_WALL)
			break ;
		ray.x += offset.x;
		ray.y += offset.y;
	}
	return ((t_ray){1, (t_fpoint){ray.x, ray.y}, angle, HORIZONTAL, NULL, 0});
}

static t_ray	check_vertical(t_map *map, t_fpoint p_pos, float angle)
{
	t_fpoint	ray;
	t_fpoint	offset;
	int			tile;

	if (angle == M_PI * 3 / 2 || angle == M_PI / 2)
		return ((t_ray){0, (t_fpoint){0, 0}, angle, VERTICAL, NULL, 0});
	ray = setup_check(&offset, (t_fpoint){p_pos.y, p_pos.x},
			(angle > M_PI / 2 && angle < M_PI * 3 / 2), tan(angle));
	offset = (t_fpoint){offset.y, offset.x};
	ray = (t_fpoint){ray.y, ray.x};
	while (distance(&p_pos, &ray) <= S_VIEW_DISTANCE)
	{
		if (ray.x < 0 || ray.y < 0 || (offset.x == -1 && ray.x - 1 < 0))
			return ((t_ray){0, (t_fpoint){0, 0}, angle, VERTICAL, NULL, 0});
		if (offset.x == -1)
			tile = (int)ray.x - 1 + (int)ray.y * map->width;
		else
			tile = (int)ray.x + (int)ray.y * map->width;
		if (tile >= 0 && tile < (int)(map->width * map->height)
			&& map->map[tile] == T_WALL)
			break ;
		ray.x += offset.x;
		ray.y += offset.y;
	}
	return ((t_ray){1, (t_fpoint){ray.x, ray.y}, angle, VERTICAL, NULL, 0});
}

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

static void	paint_wall(t_data *data, int i, t_ray *ray, t_ray_s *ray_s)
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

static void	draw_fog(int i, t_data *data, float *vertical_angle)
{
	img_square_put(&data->mlx_data.img, argb(0, 0, 0, 0),
		(t_point){i * ((float)GAME_WIDTH / data->s.ray_amount),
		(SCREEN_HEIGHT - (SCREEN_HEIGHT / S_VIEW_DISTANCE)) * *vertical_angle},
		(t_point){((float)GAME_WIDTH / data->s.ray_amount) + 1,
		SCREEN_HEIGHT / S_VIEW_DISTANCE});
}

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
		paint_wall(data, i, ray, &ray_s);
	}
	else
		draw_fog(i, data, &data->player.vertical_angle);
}

void	draw_rays(t_data *data, t_map *map, t_player *player)
{
	t_ray		ray_horizontal;
	t_ray		ray_vertical;
	t_ray		ray;
	size_t		i;

	i = 0;
	ray.angle = player->angle
		+ (data->s.angle_increment * (data->s.ray_amount / 2));
	fix_angle(&ray.angle);
	while (i < data->s.ray_amount)
	{
		ray_horizontal = check_horizontal(map, &player->pos, ray.angle);
		ray_vertical = check_vertical(map, player->pos, ray.angle);
		if (!ray_horizontal.hit_wall)
			ray = ray_vertical;
		else if (!ray_vertical.hit_wall)
			ray = ray_horizontal;
		else if (distance(&player->pos, &ray_horizontal.hit)
			< distance(&player->pos, &ray_vertical.hit))
			ray = ray_horizontal;
		else
			ray = ray_vertical;
		if (ray.orientation == HORIZONTAL && ray.angle > M_PI)
			ray.texture = &data->config.textures[1];
		else if (ray.orientation == HORIZONTAL)
			ray.texture = &data->config.textures[0];
		else if (ray.orientation == VERTICAL
			&& (ray.angle > M_PI / 2 && ray.angle < 3 * M_PI / 2))
			ray.texture = &data->config.textures[2];
		else
			ray.texture = &data->config.textures[3];
		if (ray.hit_wall)
			ray.dist_to_player = distance(&data->player.pos, &ray.hit);
		draw_ray(data, &ray, i);
		++i;
		ray.angle -= data->s.angle_increment;
		fix_angle(&ray.angle);
	}
}
