/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 14:59:55 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/31 15:32:47 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

//Draws player on minimap
static void	draw_player(t_img *img, t_player *player)
{
	img_square_put(img, argb(0, 0, 0, 255),
		(t_point){player->pos.x * TILE_SIZE + MAP_OFFSET,
		player->pos.y * TILE_SIZE + MAP_OFFSET},
		(t_point){PLAYER_SIZE, PLAYER_SIZE});
	// draw_line(img, argb(0, 0, 255, 0),
	// 	(t_point){player->pos.x * TILE_SIZE + MAP_OFFSET,
	// 	player->pos.y * TILE_SIZE + MAP_OFFSET},
	// 	(t_point){player->pos.x * TILE_SIZE + player->orientation.x * 10
	// 	+ MAP_OFFSET,
	// 	player->pos.y * TILE_SIZE + player->orientation.y * 10 + MAP_OFFSET});
}

//Maps a tile value to a color
static int	map_tile_color(int tile)
{
	if (tile == T_EMPTY)
		return (argb(MAP_ALPHA, 200, 200, 200));
	else if (tile == T_WALL)
		return (argb(MAP_ALPHA, 255, 0, 0));
	return (argb(MAP_ALPHA, 255, 255, 255));
}

//Draws minimap as an overlay
static void	draw_minimap(t_img *img, t_map *map, t_player *player)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			img_square_put(img,
				map_tile_color(map->map[x + map->width * y]),
				(t_point){x * TILE_SIZE + MAP_OFFSET,
				y * TILE_SIZE + MAP_OFFSET},
				(t_point){TILE_SIZE, TILE_SIZE});
			++x;
		}
		++y;
	}
	draw_player(img, player);
}

static void	draw_floor_ceiling(t_img *img, int *colors, float *vertical_angle)
{
	img_square_put(img, colors[1], (t_point){0, 0},
		(t_point){GAME_WIDTH, SCREEN_HEIGHT * *vertical_angle});
	img_square_put(img, colors[0],
		(t_point){0, SCREEN_HEIGHT * *vertical_angle},
		(t_point){GAME_WIDTH,
		SCREEN_HEIGHT - (SCREEN_HEIGHT * *vertical_angle)});
}

void	draw(t_data *data)
{
	draw_floor_ceiling(&data->mlx_data.img, data->config.color,
		&data->player.vertical_angle);
	draw_rays(data, &data->map, &data->player);
	if (key_pressed(KEY_TAB, &data->keys))
	{
		mlx_put_image_to_window(data->mlx_data.mlx_ptr, data->mlx_data.win_ptr,
			data->mlx_data.img.img, 0, 0);
		draw_minimap(&data->mlx_data.img, &data->map, &data->player);
	}
	mlx_put_image_to_window(data->mlx_data.mlx_ptr, data->mlx_data.win_ptr,
		data->mlx_data.img.img, 0, 0);
}
