/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:09:18 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/24 16:39:40 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main_loop(t_data *data)
{
	//REMOVE!
	usleep(10000);

	if (data->keys.keys_pressed_count)
	{
		if (key_pressed(KEY_ESCAPE, &data->keys))
			exit(0);
		control_player(data, &data->keys);
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
		init_data(argv[1], &data);
		draw(&data);
		init_loop(data.mlx_data.mlx_ptr, data.mlx_data.win_ptr, &data);
	}
	else if (argv && argv[0])
	{
		printf("Usage: %s <map.cub3D>\n", argv[0]);
		exit(1);
	}
	return (0);
}
