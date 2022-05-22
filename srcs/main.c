/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:09:18 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/22 15:47:05 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	mainLoop(t_data *data)
{
	//REMOVE!
	usleep(10000);

	if (data->keys.keys_pressed_count)
	{
		if (keyPressed(KEY_ESCAPE, &data->keys))
			exit(0);
		movePlayer(data, &data->keys);
		draw(data);
	}
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
		data.mlx_data.win_ptr = mlx_new_window(data.mlx_data.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
		if (data.mlx_data.win_ptr == NULL)
			exit(-1);
		initData(argv[1], &data);
		draw(&data);
		initLoop(data.mlx_data.mlx_ptr, data.mlx_data.win_ptr, &data);
	}
	else if (argv && argv[0])
	{
		printf("Usage: %s <map.cub3D>\n", argv[0]);
		exit(1);
	}
	return (0);
}
