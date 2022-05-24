/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:46:48 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/24 10:55:47 by vvandenb         ###   ########.fr       */
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
		ray.y = (int)player->pos.y;
		ray.x = (player->pos.y - ray.y) * (1 / tan(angle)) + player->pos.x;
		offset.y = -1;
	}
	//Looking down
	else if (angle > M_PI)
	{
		ray.y = (int)player->pos.y + 1;
		ray.x = (player->pos.y - ray.y) * (1 / tan(angle)) + player->pos.x;
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
		ray.x = (int)player->pos.x;
		ray.y = (player->pos.x - ray.x) * tan(angle) + player->pos.y;
		offset.x = -1;
	}
	//Looking right
	else if (angle < M_PI / 2 || angle > M_PI * 3 / 2)
	{
		ray.x = (int)player->pos.x + 1;
		ray.y = (player->pos.x - ray.x) * tan(angle) + player->pos.y;
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

static void	drawRay(t_img *img, t_player *player, t_fpoint *ray, size_t i, float angle)
{
	float	dist;
	int		color;
	int		height;

	if (ray->x == -1 && ray->y == -1)
		return ;
	dist = distance(&player->pos, ray);
	if (dist <= S_VIEW_DISTANCE)
	{
		color = argb(0, 200.0f * (1 - dist / S_VIEW_DISTANCE), 65.0f * (1 - dist / S_VIEW_DISTANCE), 47.0f * (1 - dist / S_VIEW_DISTANCE));
		height = SCREEN_HEIGHT / (dist * cos(angle));
		if (height < 0 || height > SCREEN_HEIGHT)
			height = SCREEN_HEIGHT;
		drawLine(img, color,
			(t_point){player->pos.x * TILE_SIZE  + GAME_WIDTH,
				player->pos.y * TILE_SIZE},
			(t_point){ray->x * TILE_SIZE + GAME_WIDTH, ray->y * TILE_SIZE});
		imgSquarePut(img, color, (t_point){i * (GAME_WIDTH / S_FOV), (SCREEN_HEIGHT - height) / 2}, (t_point){(GAME_WIDTH / S_FOV), height});
	}
}

void	drawRays(t_mlx_data *mlx, t_map *map, t_player *player)
{
	t_fpoint	ray_horizontal;
	t_fpoint	ray_vertical;
	t_fpoint	ray;
	double		angle;
	size_t		i;

	i = 0;
	angle = player->angle + (RAD1 * (S_FOV / 2));
	fixAngle(&angle);
	while (i < S_FOV)
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
		drawRay(&mlx->img, player, &ray, i, player->angle - angle);
		++i;
		angle -= RAD1;
		fixAngle(&angle);
	}
}
