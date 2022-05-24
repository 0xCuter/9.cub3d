/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:59:09 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/24 10:46:28 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	move(t_player *player, t_map *map, double angle)
{
	t_fpoint	orientation;

	orientation.x = cos(angle);
	orientation.y = -sin(angle);
	player->pos.x += orientation.x * PLAYER_SPEED;
	if (map->map[(int)(player->pos.x - 0.1) + (int)player->pos.y * map->width] == T_WALL)
		player->pos.x = (int)player->pos.x + 0.1;
	if (map->map[(int)(player->pos.x + 0.1) + (int)player->pos.y * map->width] == T_WALL)
		player->pos.x = (int)(player->pos.x + 1) - 0.1;
	player->pos.y += orientation.y * PLAYER_SPEED;
	if (map->map[(int)player->pos.x + (int)(player->pos.y - 0.1) * map->width] == T_WALL)
		player->pos.y = (int)player->pos.y + 0.1;
	if (map->map[(int)player->pos.x + (int)(player->pos.y + 0.1) * map->width] == T_WALL)
		player->pos.y = (int)(player->pos.y + 1) - 0.1;
}

void	movePlayer(t_data *data, t_keys *keys)
{
	if (keyPressed(KEY_A, keys) && !keyPressed(KEY_D, keys))
		move(&data->player, &data->map, data->player.angle + M_PI / 2);
	if (keyPressed(KEY_D, keys) && !keyPressed(KEY_A, keys))
		move(&data->player, &data->map, data->player.angle - M_PI / 2);
	if ((keyPressed(KEY_UP, keys) && !keyPressed(KEY_DOWN, keys))
		|| (keyPressed(KEY_W, keys) && !keyPressed(KEY_S, keys)))
		move(&data->player, &data->map, data->player.angle);
	if ((keyPressed(KEY_DOWN, keys) && !keyPressed(KEY_UP, keys))
		|| (keyPressed(KEY_S, keys) && !keyPressed(KEY_W, keys)))
		move(&data->player, &data->map, data->player.angle - M_PI);
	if (keyPressed(KEY_LEFT, keys) || keyPressed(KEY_RIGHT, keys))
	{
		if (keyPressed(KEY_RIGHT, keys))
			data->player.angle -= PLAYER_ROTATE_SPEED;
		if (keyPressed(KEY_LEFT, keys))
			data->player.angle += PLAYER_ROTATE_SPEED;
		fixAngle(&data->player.angle);
		data->player.orientation.x = cos(data->player.angle);
		data->player.orientation.y = -sin(data->player.angle);
	}
}
