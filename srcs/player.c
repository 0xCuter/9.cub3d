/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:59:09 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/18 19:03:44 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	move_player(t_data *data, t_keys *keys)
{
	if (key_pressed(KEY_W, keys))
		data->player.pos.y -= PLAYER_SPEED;
	if (key_pressed(KEY_S, keys))
		data->player.pos.y += PLAYER_SPEED;
	if (key_pressed(KEY_A, keys))
		data->player.pos.x -= PLAYER_SPEED;
	if (key_pressed(KEY_D, keys))
		data->player.pos.x += PLAYER_SPEED;
	if (key_pressed(KEY_UP, keys))
	{
		data->player.pos.x -= data->player.orientation.x / 5;
		data->player.pos.y -= data->player.orientation.y / 5;
	}
	if (key_pressed(KEY_DOWN, keys))
	{
		data->player.pos.x += data->player.orientation.x / 5;
		data->player.pos.y += data->player.orientation.y / 5;
	}
	if (key_pressed(KEY_LEFT, keys) || key_pressed(KEY_RIGHT, keys))
	{
		if (key_pressed(KEY_RIGHT, keys))
		{
			data->player.angle -= PLAYER_ROTATE_SPEED;
			if (data->player.angle < 0)
				data->player.angle += 2 * M_PI;
		}
		if (key_pressed(KEY_LEFT, keys))
		{
			data->player.angle += PLAYER_ROTATE_SPEED;
			if (data->player.angle >= 2 * M_PI)
				data->player.angle -= 2 * M_PI;
		}
		data->player.orientation.x = cos(data->player.angle);
		data->player.orientation.y = -sin(data->player.angle);
	}
	draw(&data->mlx_data, &data->map, &data->player);
}
