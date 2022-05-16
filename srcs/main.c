/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:09:18 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/16 11:45:51 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	map_tile_color(int tile)
{
	if (tile == T_EMPTY)
		return (rgb(200, 200, 200));
	else if (tile == T_WALL)
		return (rgb(255, 0, 0));
	return (rgb(255, 255, 255));
}

void	draw(t_mlx_data *mlx, t_map *map, t_player *player)
{
	size_t	x;
	size_t	y;
	char	tile;

	y = 0;
	while (y < map->len)
	{
		x = 0;
		while (x < map->len)
		{
			tile = map->map[x + map->len * y];
			img_square_put(&mlx->img, map_tile_color(tile),
				(t_point){x * TILE_SIZE, y * TILE_SIZE},
				(t_point){TILE_SIZE, TILE_SIZE});
			++x;
		}
		++y;
	}
	img_square_put(&mlx->img, rgb(0, 0, 255),
		(t_point){player->pos.x * TILE_SIZE, player->pos.y * TILE_SIZE},
		(t_point){TILE_SIZE, TILE_SIZE});
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img, 0, 0);
}

int	main(int argc, char **argv)
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_data	data;

	if (argc == 2)
	{
		mlx_ptr = mlx_init();
		if (mlx_ptr == NULL)
			exit(-1);
		win_ptr = mlx_new_window(mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "FdF");
		if (win_ptr == NULL)
			exit(-1);
		data.mlx_data.mlx_ptr = mlx_ptr;
		data.mlx_data.win_ptr = win_ptr;
		init_data(argv[1], &data);
		draw(&data.mlx_data, &data.map, &data.player);
		init_loop(mlx_ptr, win_ptr, &data);
	}
	else if (argv && argv[0])
	{
		printf("Usage: %s <map.cub3D>\n", argv[0]);
		exit(1);
	}
	return (0);
}
