/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:45:32 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/31 15:14:41 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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

t_ray	check_horizontal(t_map *map, t_fpoint *p_pos, float angle)
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
			tile = (int)ray.x + (int)(ray.y - 1) *map->width;
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

t_ray	check_vertical(t_map *map, t_fpoint p_pos, float angle)
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
