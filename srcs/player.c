/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:59:09 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/23 12:08:50 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	movePlayer(t_data *data, t_keys *keys)
{
	if (keyPressed(KEY_W, keys) && !keyPressed(KEY_S, keys))
	{
		data->player.pos.y -= PLAYER_SPEED;
		if (data->map.map[(int)data->player.pos.x + (int)data->player.pos.y * data->map.width] == T_WALL)
			data->player.pos.y = (int)(data->player.pos.y + 1);
	}
	if (keyPressed(KEY_S, keys) && !keyPressed(KEY_W, keys))
	{
		data->player.pos.y += PLAYER_SPEED;
		if (data->map.map[(int)data->player.pos.x + (int)(data->player.pos.y + PLAYER_TILE_RATIO) * data->map.width] == T_WALL)
			data->player.pos.y = (int)(data->player.pos.y) + (1 - PLAYER_TILE_RATIO);
	}
	if (keyPressed(KEY_A, keys) && !keyPressed(KEY_D, keys))
	{
		data->player.pos.x -= PLAYER_SPEED;
		if (data->map.map[(int)data->player.pos.x + (int)data->player.pos.y * data->map.width] == T_WALL)
			data->player.pos.x = (int)(data->player.pos.x + 1);
	}
	if (keyPressed(KEY_D, keys) && !keyPressed(KEY_A, keys))
	{
		data->player.pos.x += PLAYER_SPEED;
		if (data->map.map[(int)(data->player.pos.x + PLAYER_TILE_RATIO) + (int)data->player.pos.y * data->map.width] == T_WALL)
			data->player.pos.x = (int)(data->player.pos.x) + (1 - PLAYER_TILE_RATIO);
	}
	if (keyPressed(KEY_UP, keys) && !keyPressed(KEY_DOWN, keys))
	{
		data->player.pos.x += data->player.orientation.x * PLAYER_SPEED;
		if (data->map.map[(int)data->player.pos.x + (int)data->player.pos.y * data->map.width] == T_WALL)
			data->player.pos.x = (int)(data->player.pos.x + 1);
		else if (data->map.map[(int)(data->player.pos.x + PLAYER_TILE_RATIO) + (int)data->player.pos.y * data->map.width] == T_WALL)
			data->player.pos.x = (int)(data->player.pos.x) + (1 - PLAYER_TILE_RATIO);
		data->player.pos.y += data->player.orientation.y * PLAYER_SPEED;
		if (data->map.map[(int)data->player.pos.x + (int)data->player.pos.y * data->map.width] == T_WALL)
			data->player.pos.y = (int)(data->player.pos.y + 1);
		else if (data->map.map[(int)data->player.pos.x + (int)(data->player.pos.y + PLAYER_TILE_RATIO) * data->map.width] == T_WALL)
			data->player.pos.y = (int)(data->player.pos.y) + (1 - PLAYER_TILE_RATIO);
	}
	if (keyPressed(KEY_DOWN, keys) && !keyPressed(KEY_UP, keys))
	{
		data->player.pos.x -= data->player.orientation.x * PLAYER_SPEED;
		if (data->map.map[(int)data->player.pos.x + (int)data->player.pos.y * data->map.width] == T_WALL)
			data->player.pos.x = (int)(data->player.pos.x + 1);
		else if (data->map.map[(int)(data->player.pos.x + PLAYER_TILE_RATIO) + (int)data->player.pos.y * data->map.width] == T_WALL)
			data->player.pos.x = (int)(data->player.pos.x) + (1 - PLAYER_TILE_RATIO);
		data->player.pos.y -= data->player.orientation.y * PLAYER_SPEED;
		if (data->map.map[(int)data->player.pos.x + (int)data->player.pos.y * data->map.width] == T_WALL)
			data->player.pos.y = (int)(data->player.pos.y + 1);
		else if (data->map.map[(int)data->player.pos.x + (int)(data->player.pos.y + PLAYER_TILE_RATIO) * data->map.width] == T_WALL)
			data->player.pos.y = (int)(data->player.pos.y) + (1 - PLAYER_TILE_RATIO);
	}
	if (keyPressed(KEY_LEFT, keys) || keyPressed(KEY_RIGHT, keys))
	{
		if (keyPressed(KEY_RIGHT, keys))
		{
			data->player.angle -= PLAYER_ROTATE_SPEED;
			if (data->player.angle < 0)
				data->player.angle += 2 * M_PI;
		}
		if (keyPressed(KEY_LEFT, keys))
		{
			data->player.angle += PLAYER_ROTATE_SPEED;
			if (data->player.angle >= 2 * M_PI)
				data->player.angle -= 2 * M_PI;
		}
		data->player.orientation.x = cos(data->player.angle);
		data->player.orientation.y = -sin(data->player.angle);
	}
}
