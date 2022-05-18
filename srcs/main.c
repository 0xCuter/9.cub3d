/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:09:18 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/18 13:38:15 by vvandenb         ###   ########.fr       */
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

void	drawRay(t_mlx_data *mlx, t_map *map, t_player *player)
{
	double		ray_angle;
	t_fpoint	ray;
	t_fpoint	offset;
	size_t		dof;

	ray_angle = player->angle;
	if ((ray_angle >= M_PI - 0.001 && ray_angle <= M_PI + 0.001)
		|| (ray_angle >= -0.001 && ray_angle <= 0.001))
		return ;
	dof = 0;
	if (ray_angle < M_PI)
	{
		ray.y = (int)(player->pos.y + 0.5);
		ray.x = ((player->pos.y + 0.5) - ray.y) * (1 / tan(ray_angle)) + player->pos.x + 0.5;
		offset.y = -1;
	}
	else if (ray_angle > M_PI)
	{
		ray.y = (int)(player->pos.y + 0.5) + 1;
		ray.x = ((player->pos.y + 0.5) - ray.y) * (1 / tan(ray_angle)) + player->pos.x + 0.5;
		offset.y = 1;
	}
	offset.x = -offset.y * (1 / tan(ray_angle));
	while (dof < S_DOF)
	{
		if (ray.x > 0 && ray.x < map->len && ray.y > 0 && ray.y - 1 < map->len
			&& map->map[(int)ray.x + (int)(ray.y - 1) * map->len] == T_WALL)
			break ;
		ray.x += offset.x;
		ray.y += offset.y;
		++dof;
	}
	if (dof != S_DOF)
		draw_line(&mlx->img, rgb(0, 255, 0),
			(t_point){player->pos.x * TILE_SIZE + PLAYER_SIZE / 2, player->pos.y * TILE_SIZE + PLAYER_SIZE / 2},
			(t_point){ray.x * TILE_SIZE,
				ray.y * TILE_SIZE});
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
		(t_point){PLAYER_SIZE, PLAYER_SIZE});
	draw_line(&mlx->img, rgb(255, 0, 255),
		(t_point){player->pos.x * TILE_SIZE + PLAYER_SIZE / 2, player->pos.y * TILE_SIZE + PLAYER_SIZE / 2},
		(t_point){player->pos.x * TILE_SIZE + PLAYER_SIZE / 2 + player->orientation.x * 10,
			player->pos.y * TILE_SIZE + PLAYER_SIZE / 2 + player->orientation.y * 10});
	drawRay(mlx, map, player);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img, 0, 0);
}

int	main_loop(t_data *data)
{
	//REMOVE!
	usleep(10000);

	if (key_pressed(KEY_ESCAPE, &data->keys))
		exit(0);
	move_player(data, &data->keys);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 2)
	{
		data.mlx_data.mlx_ptr = mlx_init();
		if (data.mlx_data.mlx_ptr == NULL)
			exit(-1);
		data.mlx_data.win_ptr = mlx_new_window(data.mlx_data.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "FdF");
		if (data.mlx_data.win_ptr == NULL)
			exit(-1);
		init_data(argv[1], &data);
		draw(&data.mlx_data, &data.map, &data.player);
		init_loop(data.mlx_data.mlx_ptr, data.mlx_data.win_ptr, &data);
	}
	else if (argv && argv[0])
	{
		printf("Usage: %s <map.cub3D>\n", argv[0]);
		exit(1);
	}
	return (0);
}
