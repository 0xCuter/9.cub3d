/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 14:59:55 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/29 14:58:07 by vvandenb         ###   ########.fr       */
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

	// static int w, h = 0;
	// static t_img	wall1;
	// if (h == 0)
	// {
	// 	wall1.img = mlx_xpm_file_to_image(data->mlx_data.mlx_ptr, "./textures/wall1.xpm", &w, &h);
	// 	wall1.addr = mlx_get_data_addr(wall1.img, &wall1.bits_per_pixel, &wall1.line_len, &wall1.endian);
	// 	printf("%i %i\n", h, w);
	// 	printf("%i %i %i\n", wall1.bits_per_pixel, wall1.line_len, wall1.endian);
	// }

	// t_point	pos = {0, 0};
	// int	zoom = 2;
	// while (pos.y / zoom < h)
	// {
	// 	pos.x = 0;
	// 	while (pos.x / zoom < w)
	// 	{
	// 		img_square_put(&data->mlx_data.img, ((int *)wall1.addr)[pos.x / zoom + pos.y / zoom * h],
	// 			pos, (t_point){zoom, zoom});
	// 		pos.x += zoom;
	// 	}
	// 	pos.y += zoom;
	// }
	mlx_put_image_to_window(data->mlx_data.mlx_ptr, data->mlx_data.win_ptr, data->mlx_data.img.img, 0, 0);
	// mlx_put_image_to_window(data->mlx_data.mlx_ptr, data->mlx_data.win_ptr, wall1.img, 0, 0);
}
