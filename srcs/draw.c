/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 14:59:55 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/25 16:39:17 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

//Maps a tile value to a color
static int	map_tile_color(int tile)
{
	if (tile == T_EMPTY)
		return (argb(0, 200, 200, 200));
	else if (tile == T_WALL)
		return (argb(0, 255, 0, 0));
	return (argb(0, 255, 255, 255));
}

//Draws minimap with player
static void	draw_map(t_mlx_data *mlx, t_map *map, t_player *player)
{
	// (void)map;
	size_t	x;
	size_t	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			img_square_put(&mlx->img, map_tile_color(map->map[x + map->width * y]),
				(t_point){x * TILE_SIZE + GAME_WIDTH, y * TILE_SIZE},
				(t_point){TILE_SIZE, TILE_SIZE});
			++x;
		}
		++y;
	}
	img_square_put(&mlx->img, argb(0, 0, 0, 255),
		(t_point){player->pos.x * TILE_SIZE + GAME_WIDTH, player->pos.y * TILE_SIZE},
		(t_point){PLAYER_SIZE, PLAYER_SIZE});
	draw_line(&mlx->img, argb(0, 0, 255, 0),
		(t_point){player->pos.x * TILE_SIZE + GAME_WIDTH, player->pos.y * TILE_SIZE},
		(t_point){player->pos.x * TILE_SIZE + player->orientation.x * 10 + GAME_WIDTH,
			player->pos.y * TILE_SIZE + player->orientation.y * 10});
}

void	draw(t_data *data)
{
	draw_map(&data->mlx_data, &data->map, &data->player);
	img_square_put(&data->mlx_data.img, argb(0, CEILING_R, CEILING_G, CEILING_B),
		(t_point){0, 0}, (t_point){GAME_WIDTH, SCREEN_HEIGHT * data->player.vertical_angle});
	img_square_put(&data->mlx_data.img, argb(0, FLOOR_R, FLOOR_G, FLOOR_B),
		(t_point){0, SCREEN_HEIGHT * data->player.vertical_angle}, (t_point){GAME_WIDTH, SCREEN_HEIGHT - (SCREEN_HEIGHT * data->player.vertical_angle)});
	draw_rays(&data->mlx_data, &data->map, &data->player);

	// int w, h;
	// static void	*wall1 = NULL;
	// if (wall1 == NULL)
	// 	wall1 = mlx_xpm_file_to_image(data->mlx_data.mlx_ptr, "./textures/wall1.xpm", &w, &h);
	// mlx_put_image_to_window(data->mlx_data.mlx_ptr, data->mlx_data.win_ptr, wall1, 0, 0);

	mlx_put_image_to_window(data->mlx_data.mlx_ptr, data->mlx_data.win_ptr, data->mlx_data.img.img, 0, 0);
}
