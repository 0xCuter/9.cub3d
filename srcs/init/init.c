/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 10:45:52 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/24 18:19:07 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

//Exits if the file does not end with ".cub"
static void	check_format(char *name, int fd)
{
	size_t	len;

	if (name)
	{
		len = ft_strlen(name);
		if (len < 4
			|| name[len - 4] != '.'
			|| name[len - 3] != 'c'
			|| name[len - 2] != 'u'
			|| name[len - 1] != 'b')
			exit_close_error("Wrong map format\n", 1, fd);
	}
}

void	init_data(char *map_name, t_data *data)
{
	int		fd;
	char	*line;

	fd = safe_open(map_name, O_RDONLY);
	check_format(map_name, fd);
	line = get_next_line(fd);
	if (line == NULL)
		exit_close_error("Could not read file\n", 1, fd);
	init_infos(data, line, fd);
	init_map(data, line, fd, map_name);
	data->keys.keys_pressed_count = 0;
	data->mlx_data.img.img = mlx_new_image(
			data->mlx_data.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->mlx_data.img.addr = mlx_get_data_addr(
			data->mlx_data.img.img, &data->mlx_data.img.bits_per_pixel,
			&data->mlx_data.img.line_len, &data->mlx_data.img.endian);
}

//Called when pressing window close
static int	exit_program()
{
	exit(0);
}

void	init_loop(void *mlx_ptr, void *win_ptr, t_data *data)
{
	mlx_hook(win_ptr, KeyPress, KeyPressMask, key_press_hook, &data->keys);
	mlx_hook(win_ptr, KeyRelease, KeyReleaseMask, key_release_hook, &data->keys);
	mlx_hook(win_ptr, DestroyNotify, 0, exit_program, NULL);
	mlx_loop_hook(mlx_ptr, main_loop, data);
	mlx_loop(mlx_ptr);
}
