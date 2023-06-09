/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 10:45:52 by vvandenb          #+#    #+#             */
/*   Updated: 2022/06/01 09:49:39 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	init_settings(t_settings *s)
{
	s->shade = S_SHADE;
	s->view_distance = S_VIEW_DISTANCE;
	s->fov = S_FOV;
	s->ray_amount = S_FOV * S_RAYS_AMOUNT_MULTIPLIER;
	s->angle_increment = RAD1 / S_RAYS_AMOUNT_MULTIPLIER;
}

//Exits if the file does not have the correct extension
void	check_ext(char *name, char *ext, int fd)
{
	size_t	len;

	if (name)
	{
		len = ft_strlen(name);
		if (len < 4
			|| name[len - 4] != '.'
			|| name[len - 3] != ext[0]
			|| name[len - 2] != ext[1]
			|| name[len - 1] != ext[2])
			exit_close_error("File extension is invalid\n", 1, fd);
	}
}

//Inits the `t_data` structure
void	init_data(char *map_name, t_data *data)
{
	int		fd;
	char	*line;

	init_settings(&data->s);
	fd = safe_open(map_name, O_RDONLY);
	check_ext(map_name, "cub", fd);
	line = get_next_line(fd);
	if (line == NULL)
		exit_close_error("Could not read file\n", 1, fd);
	line = parse_config(data, line, fd);
	init_map(data, line, fd, map_name);
	data->keys.keys_pressed_count = 0;
	data->mlx_data.img.img = mlx_new_image(
			data->mlx_data.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->mlx_data.img.addr = mlx_get_data_addr(
			data->mlx_data.img.img, &data->mlx_data.img.bits_per_pixel,
			&data->mlx_data.img.line_len, &data->mlx_data.img.endian);
}

//Called when pressing window close
static int	exit_program(void)
{
	exit(0);
}

//Sets up hooks and launches the main loop
void	init_loop(void *mlx_ptr, void *win_ptr, t_data *data)
{
	mlx_hook(win_ptr, KeyPress, KeyPressMask,
		key_press_hook, &data->keys);
	mlx_hook(win_ptr, KeyRelease, KeyReleaseMask,
		key_release_hook, &data->keys);
	mlx_hook(win_ptr, DestroyNotify, 0,
		exit_program, NULL);
	mlx_loop_hook(mlx_ptr, main_loop, data);
	mlx_loop(mlx_ptr);
}
