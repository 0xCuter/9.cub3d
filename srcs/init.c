/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 10:45:52 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/18 10:45:23 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

//Inits player if it finds it in the map
static char	find_player(t_data *data, char *line, int i)
{
	char	*player;

	player = ft_strchr(line, 'N');
	if (player == NULL)
		player = ft_strchr(line, 'S');
	if (player == NULL)
		player = ft_strchr(line, 'W');
	if (player == NULL)
		player = ft_strchr(line, 'E');
	if (player)
	{
		if (*player == 'E')
			data->player.angle = 0;
		if (*player == 'N')
			data->player.angle = M_PI / 2;
		if (*player == 'W')
			data->player.angle = M_PI;
		if (*player == 'S')
			data->player.angle = M_PI * 3 / 2;
		data->player.orientation.x = cos(data->player.angle);
		data->player.orientation.y = -sin(data->player.angle);
		data->player.pos = (t_fpoint){player - line, i / data->map.len};
		*player = '0';
		return (1);
	}
	return (0);
}

//Inits a `t_map` structure
static void	fill_map(char *line, t_data *data, int fd)
{
	size_t	i;
	char	b_player_found;

	i = 0;
	b_player_found = 0;
	while (line)
	{
		if (!b_player_found)
			b_player_found = find_player(data, line, i);
		ft_strlcpy(data->map.map + i, line, data->map.len + 1);
		free(line);
		line = get_next_line(fd);
		i += data->map.len;
	}
	if (!b_player_found)
		exit_error("Could not find a player's start position\n", 1);
}

void	init_data(char *map_name, t_data *data)
{
	int		fd;
	char	*line;

	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		exit_perror("MAP", fd);
	line = get_next_line(fd);
	if (line == NULL)
		exit_error("Could not read map\n", 1);
	data->keys.keys_pressed_count = 0;
	data->map.len = ft_strlen(line) - 1;
	data->mlx_data.img.img = mlx_new_image(
			data->mlx_data.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->mlx_data.img.addr = mlx_get_data_addr(
			data->mlx_data.img.img, &data->mlx_data.img.bits_per_pixel,
			&data->mlx_data.img.line_len, &data->mlx_data.img.endian);
	data->map.map = malloc((data->map.len * data->map.len) * sizeof(char));
	if (data->map.map == NULL)
		return ;
	fill_map(line, data, fd);
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
