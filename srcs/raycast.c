/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:46:48 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/30 17:14:00 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static float	distance(t_fpoint *p1, t_fpoint *p2)
{
	return (sqrt((p1->y - p2->y) * (p1->y - p2->y) + (p1->x - p2->x) * (p1->x - p2->x)));
}

static t_fpoint	check_horizontal(t_map *map, t_player *player, float angle)
{
	t_fpoint	ray;
	t_fpoint	offset;
	size_t		dof;
	int 		tile;

	if ((angle >= M_PI - 0.001 && angle <= M_PI + 0.001)
		|| (angle >= -0.001 && angle <= 0.001))
		return (t_fpoint){-1, -1};
	dof = 0;
	if (angle < M_PI)
	{
		ray.y = (int)player->pos.y;
		ray.x = (player->pos.y - ray.y) * (1 / tan(angle)) + player->pos.x;
		offset.y = -1;
	}
	else if (angle > M_PI)
	{
		ray.y = (int)player->pos.y + 1;
		ray.x = (player->pos.y - ray.y) * (1 / tan(angle)) + player->pos.x;
		offset.y = 1;
	}
	offset.x = -offset.y * (1 / tan(angle));
	while (distance(&player->pos, &ray) <= S_VIEW_DISTANCE)
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
	return (ray);
}

static t_fpoint	check_vertical(t_map *map, t_player *player, float angle)
{
	t_fpoint	ray;
	t_fpoint	offset;
	size_t		dof;
	int 		tile;

	if ((angle >= M_PI / 2 - 0.001 && angle <= M_PI / 2 + 0.001)
		|| (angle >= M_PI * 3 / 2 - 0.001 && angle <= M_PI * 3 / 2 + 0.001))
		return (t_fpoint){-1, -1};
	dof = 0;
	if (angle > M_PI / 2 && angle < M_PI * 3 / 2)
	{
		ray.x = (int)player->pos.x;
		ray.y = (player->pos.x - ray.x) * tan(angle) + player->pos.y;
		offset.x = -1;
	}
	else if (angle < M_PI / 2 || angle > M_PI * 3 / 2)
	{
		ray.x = (int)player->pos.x + 1;
		ray.y = (player->pos.x - ray.x) * tan(angle) + player->pos.y;
		offset.x = 1;
	}
	offset.y = -offset.x * tan(angle);
	while (distance(&player->pos, &ray) <= S_VIEW_DISTANCE)
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
	return (ray);
}

static void	draw_ray(t_img *img, t_player *player, t_fpoint *ray, size_t i,
	float angle, float dif_angle, t_texture *texture, char ray_type)
{
	float	dist;
	int		color;
	int		wall_height;

	dist = distance(&player->pos, ray);
	if (dist <= S_VIEW_DISTANCE && (ray->x != -1 && ray->y != -1))
	{
		color = argb(0, 200.0f * (1 - dist / S_VIEW_DISTANCE), 65.0f * (1 - dist / S_VIEW_DISTANCE), 47.0f * (1 - dist / S_VIEW_DISTANCE));
		wall_height = SCREEN_HEIGHT / (dist * cos(dif_angle));
		float	text_step_y = (float)texture->size.y / wall_height;
		float	tex_y_offset = 0;
		if (wall_height < 0 || wall_height > SCREEN_HEIGHT)
		{
			tex_y_offset = (wall_height - SCREEN_HEIGHT) / 2;
			wall_height = SCREEN_HEIGHT;
		}
		draw_line(img, color,
			(t_point){player->pos.x * TILE_SIZE + GAME_WIDTH,
			player->pos.y * TILE_SIZE},
			(t_point){ray->x * TILE_SIZE + GAME_WIDTH, ray->y * TILE_SIZE});

		float wall_offset;
		if (ray_type == HORIZONTAL)
			wall_offset = ray->x;
		else
			wall_offset = ray->y;
		wall_offset -= floor((wall_offset));

		int		y = (SCREEN_HEIGHT - wall_height) * player->vertical_angle;
		float 	wall_width = ((float)GAME_WIDTH / S_FOV);
		int		draw_height = y + wall_height;
		float	tex_y = text_step_y * tex_y_offset;
		int		x = i * wall_width;
		while (y < draw_height)
		{
			int		color;
			float	tex_x;

			tex_x = wall_offset * texture->size.x;
			if (ray_type == HORIZONTAL)
			{
				if (angle > M_PI)
					color = ((int *)texture->img.addr)[(int)(texture->size.x - tex_x) + texture->size.y * (int)tex_y];
				else
					color = ((int *)texture->img.addr)[(int)tex_x + texture->size.y * (int)tex_y];
			}
			else
			{
				if (angle > M_PI / 2 && angle < 3 * M_PI / 2)
					color = ((int *)texture->img.addr)[(int)(texture->size.x - tex_x) + texture->size.y * (int)tex_y];
				else
					color = ((int *)texture->img.addr)[(int)tex_x + texture->size.y * (int)tex_y];
			}
			if(ray_type == VERTICAL)
				color = (color >> 1) & 8355711;

			if (wall_width < 1)
				img_square_put(img, color, (t_point){x, y}, (t_point){1, 1});
			else
				img_square_put(img, color, (t_point){x, y}, (t_point){wall_width + 1, 1});
			tex_y += text_step_y;
			++y;
		}
	}
	else
		img_square_put(img, argb(0, 0, 0, 0), (t_point){i * (GAME_WIDTH / S_FOV),
			(SCREEN_HEIGHT - (SCREEN_HEIGHT / S_VIEW_DISTANCE)) * player->vertical_angle},
			(t_point){(GAME_WIDTH / S_FOV), SCREEN_HEIGHT / S_VIEW_DISTANCE});
}

void	draw_rays(t_data *data, t_map *map, t_player *player)
{
	t_fpoint	ray_horizontal;
	t_fpoint	ray_vertical;
	t_fpoint	ray;
	double		angle;
	size_t		i;
	char		ray_type;
	t_texture	*texture;

	i = 0;
	angle = player->angle + (RAD1 * (S_FOV / 2));
	fix_angle(&angle);
	while (i < S_FOV)
	{
		ray_horizontal = check_horizontal(map, player, angle);
		ray_vertical = check_vertical(map, player, angle);
		if (ray_horizontal.x == -1 && ray_horizontal.y == -1)
		{
			ray_type = VERTICAL;
			ray = ray_vertical;
		}
		else if (ray_vertical.x == -1 && ray_vertical.y == -1)
		{
			ray_type = HORIZONTAL;
			ray = ray_horizontal;
		}
		else if (distance(&player->pos, &ray_horizontal) < distance(&player->pos, &ray_vertical))
		{
			ray_type = HORIZONTAL;
			ray = ray_horizontal;
		}
		else
		{
			ray_type = VERTICAL;
			ray = ray_vertical;
		}
		if (ray_type == HORIZONTAL && angle > M_PI)
			texture = &data->config.textures[1];
		else if (ray_type == HORIZONTAL)
			texture = &data->config.textures[0];
		else if (ray_type == VERTICAL && (angle > M_PI / 2 && angle < 3 * M_PI / 2))
			texture = &data->config.textures[2];
		else
			texture = &data->config.textures[3];
		draw_ray(&data->mlx_data.img, player, &ray, i, angle, player->angle - angle, texture, ray_type);
		++i;
		angle -= RAD1;
		fix_angle(&angle);
	}
}
