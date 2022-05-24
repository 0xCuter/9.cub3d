/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:59:09 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/24 11:10:23 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	move(t_player *player, t_map *map, double angle)
{
	t_fpoint	orientation;

	orientation.x = cos(angle);
	orientation.y = -sin(angle);
	player->pos.x += orientation.x * PLAYER_SPEED;
	if (map->map[(int)(player->pos.x - 0.1) + (int)player->pos.y * map->width]
		== T_WALL)
		player->pos.x = (int)player->pos.x + 0.1;
	if (map->map[(int)(player->pos.x + 0.1) + (int)player->pos.y * map->width]
		== T_WALL)
		player->pos.x = (int)(player->pos.x + 1) - 0.1;
	player->pos.y += orientation.y * PLAYER_SPEED;
	if (map->map[(int)player->pos.x + (int)(player->pos.y - 0.1) * map->width]
		== T_WALL)
		player->pos.y = (int)player->pos.y + 0.1;
	if (map->map[(int)player->pos.x + (int)(player->pos.y + 0.1) * map->width]
		== T_WALL)
		player->pos.y = (int)(player->pos.y + 1) - 0.1;
}

void	move_player(t_data *data, t_keys *keys)
{
	if (key_pressed(KEY_A, keys) && !key_pressed(KEY_D, keys))
		move(&data->player, &data->map, data->player.angle + M_PI / 2);
	if (key_pressed(KEY_D, keys) && !key_pressed(KEY_A, keys))
		move(&data->player, &data->map, data->player.angle - M_PI / 2);
	if ((key_pressed(KEY_UP, keys) && !key_pressed(KEY_DOWN, keys))
		|| (key_pressed(KEY_W, keys) && !key_pressed(KEY_S, keys)))
		move(&data->player, &data->map, data->player.angle);
	if ((key_pressed(KEY_DOWN, keys) && !key_pressed(KEY_UP, keys))
		|| (key_pressed(KEY_S, keys) && !key_pressed(KEY_W, keys)))
		move(&data->player, &data->map, data->player.angle - M_PI);
	if (key_pressed(KEY_LEFT, keys) || key_pressed(KEY_RIGHT, keys))
	{
		if (key_pressed(KEY_RIGHT, keys))
			data->player.angle -= PLAYER_ROTATE_SPEED;
		if (key_pressed(KEY_LEFT, keys))
			data->player.angle += PLAYER_ROTATE_SPEED;
		fix_angle(&data->player.angle);
		data->player.orientation.x = cos(data->player.angle);
		data->player.orientation.y = -sin(data->player.angle);
	}
}
