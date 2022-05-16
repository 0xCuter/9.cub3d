/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:31:07 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/16 18:34:26 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	move_player(t_data *data, int keycode)
{
	if (keycode == KEY_W)
		data->player.pos.y -= PLAYER_SPEED;
	else if (keycode == KEY_S)
		data->player.pos.y += PLAYER_SPEED;
	else if (keycode == KEY_A)
		data->player.pos.x -= PLAYER_SPEED;
	else if (keycode == KEY_D)
		data->player.pos.x += PLAYER_SPEED;
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
	{
		if (keycode == KEY_LEFT)
		{
			data->player.angle -= PLAYER_ROTATE_SPEED;
			if (data->player.angle < 0)
				data->player.angle = 2 * M_PI;
		}
		if (keycode == KEY_RIGHT)
		{
			data->player.angle += PLAYER_ROTATE_SPEED;
			if (data->player.angle > 2 * M_PI)
				data->player.angle = 0;
		}
		data->player.orientation.x = cos(data->player.angle);
		data->player.orientation.y = sin(data->player.angle);
	}
	draw(&data->mlx_data, &data->map, &data->player);
}

int	key_press_hook(int keycode, t_data *data)
{
	// printf("%i\n", keycode);
	if (keycode == KEY_ESCAPE)
		exit(0);
	move_player(data, keycode);
	return (0);
}

int	mouse_hook(int button, int x, int y, void *param)
{
	(void)button;
	(void)x;
	(void)y;
	(void)param;
	return (0);
}
