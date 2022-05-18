/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:31:07 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/17 17:41:36 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	key_pressed(int keycode, t_keys *keys)
{
	size_t	i;

	i = 0;
	while (i < keys->keys_pressed_count)
	{
		if (keys->keys[i] == keycode)
			return (1);
		++i;
	}
	return (0);
}

int	key_press_hook(int keycode, t_keys *keys)
{
	if (keys->keys_pressed_count == MAX_KEYS_PRESSED || key_pressed(keycode, keys))
		return (0);
	// printf("PRESSED: %i\n", keycode);
	keys->keys[keys->keys_pressed_count] = keycode;
	++keys->keys_pressed_count;
	return (0);
}

int	key_release_hook(int keycode, t_keys *keys)
{
	size_t	i;

	if (keys->keys_pressed_count == 0 || !key_pressed(keycode, keys))
		return (0);
	// printf("RELEASED: %i\n", keycode);
	i = 0;
	while (i < keys->keys_pressed_count)
	{
		if (keys->keys[i] == keycode)
		{
			keys->keys[i] = keys->keys[keys->keys_pressed_count - 1];
			--keys->keys_pressed_count;
			return (0);
		}
		++i;
	}
	return (0);
}

// int	mouse_hook(int button, int x, int y, void *param)
// {
// 	(void)button;
// 	(void)x;
// 	(void)y;
// 	(void)param;
// 	return (0);
// }
