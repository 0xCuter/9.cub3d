/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:59:09 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/25 16:12:18 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

//Moves player if no collisions are detected
static void	move(t_player *player, t_map *map, double angle)
{
	t_fpoint	orientation;
	t_fpoint	prev_pos;

	orientation.x = cos(angle);
	orientation.y = -sin(angle);
	prev_pos = player->pos;
	player->pos.x += orientation.x * PLAYER_SPEED;
	if (map->map[(int)player->pos.x + (int)player->pos.y * map->width]
		== T_WALL)
		player->pos.x = prev_pos.x;
	player->pos.y += orientation.y * PLAYER_SPEED;
	if (map->map[(int)player->pos.x + (int)player->pos.y * map->width]
		== T_WALL)
		player->pos.y = prev_pos.y;
}

void	control_player(t_data *data, t_keys *keys)
{
	if (key_pressed(KEY_A, keys) && !key_pressed(KEY_D, keys))
		move(&data->player, &data->map, data->player.angle + M_PI / 2);
	if (key_pressed(KEY_D, keys) && !key_pressed(KEY_A, keys))
		move(&data->player, &data->map, data->player.angle - M_PI / 2);
	if (key_pressed(KEY_UP, keys) && !key_pressed(KEY_DOWN, keys)
		&& data->player.vertical_angle + PLAYER_VERTICAL_SPEED <= 1)
		data->player.vertical_angle += PLAYER_VERTICAL_SPEED;
	if (key_pressed(KEY_DOWN, keys) && !key_pressed(KEY_UP, keys)
		&& data->player.vertical_angle - PLAYER_VERTICAL_SPEED >= 0)
		data->player.vertical_angle -= PLAYER_VERTICAL_SPEED;
	if (key_pressed(KEY_W, keys) && !key_pressed(KEY_S, keys))
		move(&data->player, &data->map, data->player.angle);
	if (key_pressed(KEY_S, keys) && !key_pressed(KEY_W, keys))
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
