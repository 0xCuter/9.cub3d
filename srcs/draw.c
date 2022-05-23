/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 14:59:55 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/23 12:40:37 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

//Maps a tile value to a color
static int	mapTileColor(int tile)
{
	if (tile == T_EMPTY)
		return (argb(0, 200, 200, 200));
	else if (tile == T_WALL)
		return (argb(0, 255, 0, 0));
	return (argb(0, 255, 255, 255));
}

//Draws minimap with player
static void	drawMap(t_mlx_data *mlx, t_map *map, t_player *player)
{
	size_t	x;
	size_t	y;
	char	tile;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			tile = map->map[x + map->width * y];
			imgSquarePut(&mlx->img, mapTileColor(tile),
				(t_point){x * TILE_SIZE + GAME_WIDTH, y * TILE_SIZE},
				(t_point){TILE_SIZE, TILE_SIZE});
			++x;
		}
		++y;
	}
	imgSquarePut(&mlx->img, argb(0, 0, 0, 255),
		(t_point){player->pos.x * TILE_SIZE + GAME_WIDTH, player->pos.y * TILE_SIZE},
		(t_point){PLAYER_SIZE, PLAYER_SIZE});
	drawLine(&mlx->img, argb(0, 0, 255, 0),
		(t_point){player->pos.x * TILE_SIZE + PLAYER_SIZE / 2 + GAME_WIDTH, player->pos.y * TILE_SIZE + PLAYER_SIZE / 2},
		(t_point){player->pos.x * TILE_SIZE + PLAYER_SIZE / 2 + player->orientation.x * 10 + GAME_WIDTH,
			player->pos.y * TILE_SIZE + PLAYER_SIZE / 2 + player->orientation.y * 10});
}

void	draw(t_data *data)
{
	drawMap(&data->mlx_data, &data->map, &data->player);
	drawRays(&data->mlx_data, &data->map, &data->player);
	mlx_put_image_to_window(data->mlx_data.mlx_ptr, data->mlx_data.win_ptr, data->mlx_data.img.img, 0, 0);
}
