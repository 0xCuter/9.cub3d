/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:31:07 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/16 11:43:06 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	move_player(t_data *data, int keycode)
{
	if (keycode == KEY_W)
		--data->player.pos.y;
	else if (keycode == KEY_S)
		++data->player.pos.y;
	else if (keycode == KEY_A)
		--data->player.pos.x;
	else if (keycode == KEY_D)
		++data->player.pos.x;
	draw(&data->mlx_data, &data->map, &data->player);
}

int	key_press_hook(int keycode, t_data *data)
{
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
