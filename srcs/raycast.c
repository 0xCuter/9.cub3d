/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:46:48 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/19 15:30:41 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_fpoint	check_horizontal(t_map *map, t_player *player, float angle)
{
	t_fpoint	ray;
	t_fpoint	offset;
	size_t		dof;

	if ((angle >= M_PI - 0.001 && angle <= M_PI + 0.001)
		|| (angle >= -0.001 && angle <= 0.001))
		return (t_fpoint){-1, -1};
	dof = 0;
	//Looking up
	if (angle < M_PI)
	{
		ray.y = (int)(player->pos.y + (PLAYER_TILE_RATIO / 2));
		ray.x = ((player->pos.y + (PLAYER_TILE_RATIO / 2)) - ray.y) * (1 / tan(angle)) + player->pos.x + (PLAYER_TILE_RATIO / 2);
		offset.y = -1;
	}
	//Looking down
	else if (angle > M_PI)
	{
		ray.y = (int)(player->pos.y + (PLAYER_TILE_RATIO / 2)) + 1;
		ray.x = ((player->pos.y + (PLAYER_TILE_RATIO / 2)) - ray.y) * (1 / tan(angle)) + player->pos.x + (PLAYER_TILE_RATIO / 2);
		offset.y = 1;
	}
	offset.x = -offset.y * (1 / tan(angle));
	int tile;
	while (dof < MAX_RAY_LOOPS)
	{
		if (ray.x < 0 || ray.y < 0 || (offset.y == -1 && ray.y - 1 < 0))
			return (t_fpoint){-1, -1};
		if (offset.y == -1)
			tile = (int)ray.x + (int)(ray.y - 1) * map->width;
		else
			tile = (int)ray.x + (int)ray.y * map->width;
		if (tile >= 0 && tile < (int)(map->width * map->height) && map->map[tile] == T_WALL)
			break ;
		ray.x += offset.x;
		ray.y += offset.y;
		++dof;
	}
	if (dof < MAX_RAY_LOOPS)
		return (ray);
	return (t_fpoint){-1, -1};
}

static t_fpoint	check_vertical(t_map *map, t_player *player, float angle)
{
	t_fpoint	ray;
	t_fpoint	offset;
	size_t		dof;

	if ((angle >= M_PI / 2 - 0.001 && angle <= M_PI / 2 + 0.001)
		|| (angle >= M_PI * 3 / 2 - 0.001 && angle <= M_PI * 3 / 2 + 0.001))
		return (t_fpoint){-1, -1};
	dof = 0;
	//Looking left
	if (angle > M_PI / 2 && angle < M_PI * 3 / 2)
	{
		ray.x = (int)(player->pos.x + (PLAYER_TILE_RATIO / 2));
		ray.y = ((player->pos.x + (PLAYER_TILE_RATIO / 2)) - ray.x) * tan(angle) + player->pos.y + (PLAYER_TILE_RATIO / 2);
		offset.x = -1;
	}
	//Looking right
	else if (angle < M_PI / 2 || angle > M_PI * 3 / 2)
	{
		ray.x = (int)(player->pos.x + (PLAYER_TILE_RATIO / 2)) + 1;
		ray.y = ((player->pos.x + (PLAYER_TILE_RATIO / 2)) - ray.x) * tan(angle) + player->pos.y + (PLAYER_TILE_RATIO / 2);
		offset.x = 1;
	}
	offset.y = -offset.x * tan(angle);
	int tile;
	while (dof < MAX_RAY_LOOPS)
	{
		if (ray.x < 0 || ray.y < 0 || (offset.x == -1 && ray.x - 1 < 0))
			return (t_fpoint){-1, -1};
		if (offset.x == -1)
			tile = (int)ray.x - 1 + (int)ray.y * map->width;
		else
			tile = (int)ray.x + (int)ray.y * map->width;
		if (tile >= 0 && tile < (int)(map->width * map->height) && map->map[tile] == T_WALL)
			break ;
		ray.x += offset.x;
		ray.y += offset.y;
		++dof;
	}
	if (dof < MAX_RAY_LOOPS)
		return (ray);
	return (t_fpoint){-1, -1};
}

static float	distance(t_fpoint *p1, t_fpoint *p2)
{
	return (sqrt((p1->y - p2->y) * (p1->y - p2->y) + (p1->x - p2->x) * (p1->x - p2->x)));
}

void	drawRay(t_img *img, t_player *player, int color, t_fpoint *ray)
{
	draw_line(img, color,
		(t_point){player->pos.x * TILE_SIZE + PLAYER_SIZE / 2 + MAP_OFFSET,
			player->pos.y * TILE_SIZE + PLAYER_SIZE / 2},
		(t_point){ray->x * TILE_SIZE + MAP_OFFSET, ray->y * TILE_SIZE});
}

void	drawRays(t_mlx_data *mlx, t_map *map, t_player *player)
{
	t_fpoint	ray_horizontal;
	t_fpoint	ray_vertical;
	t_fpoint	ray;
	float		angle;
	size_t		i;
	(void)ray;

	i = S_FOV;
	angle = player->angle - (RAD1 * (S_FOV / 2));
	if (angle < 0)
		angle += 2 * M_PI;
	if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	while (i)
	{
		ray_horizontal = check_horizontal(map, player, angle);
		ray_vertical = check_vertical(map, player, angle);
		if (ray_horizontal.x == -1 && ray_horizontal.y == -1)
			ray = ray_vertical;
		else if (ray_vertical.x == -1 && ray_vertical.y == -1)
			ray = ray_horizontal;
		else if (distance(&player->pos, &ray_horizontal) < distance(&player->pos, &ray_vertical))
			ray = ray_horizontal;
		else
			ray = ray_vertical;
		if (ray.x != -1 && ray.y != -1 && distance(&player->pos, &ray) <= S_VIEW_DISTANCE)
			drawRay(&mlx->img, player, rgb(0, 255, 0), &ray);
		--i;
		angle += RAD1;
		if (angle < 0)
			angle += 2 * M_PI;
		if (angle > 2 * M_PI)
			angle -= 2 * M_PI;
	}
}
