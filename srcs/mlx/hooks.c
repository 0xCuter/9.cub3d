/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:31:07 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/16 00:58:29 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	move_w(t_map *map)
{
	size_t	i;

	i = 0;
	while (i < map->len * map->len)
	{
		if (map->map[i] == 'P')
		{
			if (map->map[i - map->len] != '1')
			{
				map->map[i] = '0';
				map->map[i - map->len] = 'P';
				break ;
			}
			else
				return ;
		}
		i++;
	}
	draw_map(map);
}

static void	move_a(t_map *map)
{
	size_t	i;

	i = 0;
	while (i < map->len * map->len)
	{
		if (map->map[i] == 'P')
		{
			if (map->map[i - 1] != '1')
			{
				map->map[i] = '0';
				map->map[i - 1] = 'P';
				break ;
			}
			else
				return ;
		}
		i++;
	}
	draw_map(map);
}

static void	move_s(t_map *map)
{
	size_t	i;

	i = 0;
	while (i < map->len * map->len)
	{
		if (map->map[i] == 'P')
		{
			if (map->map[i + map->len] != '1')
			{
				map->map[i] = '0';
				map->map[i + map->len] = 'P';
				break ;
			}
			else
				return ;
		}
		i++;
	}
	draw_map(map);
}

static void	move_d(t_map *map)
{
	size_t	i;

	i = 0;
	while (i < map->len * map->len)
	{
		if (map->map[i] == 'P')
		{
			if (map->map[i + 1] != '1')
			{
				map->map[i] = '0';
				map->map[i + 1] = 'P';
				break ;
			}
			else
				return ;
		}
		i++;
	}
	draw_map(map);
}

int	key_press_hook(int keycode, t_map *map)
{
	if (keycode == KEY_ESCAPE)
		exit(0);
	if (keycode == KEY_W)
		move_w(map);
	if (keycode == KEY_A)
		move_a(map);
	if (keycode == KEY_S)
		move_s(map);
	if (keycode == KEY_D)
		move_d(map);
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
