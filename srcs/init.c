/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 10:45:52 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/20 12:04:20 by vvandenb         ###   ########.fr       */
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
		data->player.pos = (t_fpoint){player - line, i / data->map.width};
		*player = '0';
		return (1);
	}
	return (0);
}

static void	get_dimensions(char *line, t_data *data, int fd)
{
	size_t	max_len;
	size_t	len;
	size_t	i;

	max_len = 0;
	i = 0;
	while (line)
	{
		len = ft_strlen(line);
		if (line[len - 1] == '\n')
			len--;
		if (len > max_len)
			max_len = len;
		free(line);
		line = get_next_line(fd);
		i++;
	}
	data->map.width = max_len;
	data->map.height = i;
	i = close(fd);
	if (i)
		exitPerror("CLOSE", i);
}

// //Inits a `t_map` structure
// static void	fill_map(char *line, t_data *data, int fd)
// {
// 	size_t	i;
// 	char	b_player_found;

// 	i = 0;
// 	b_player_found = 0;
// 	while (line)
// 	{
// 		b_player_found = find_player(data, line, i);
// 		ft_strlcpy(data->map.map + i, line, data->map.len + 1);
// 		free(line);
// 		line = get_next_line(fd);
// 		i += data->map.len;
// 	}
// 	if (!b_player_found)
// 		exitError("Could not find a player's start position\n", 1);
// }

//Inits a `t_map` structure
static void	fill_map(char *map_name, t_data *data, int fd)
{
	char	player_found;
	char	*line;
	size_t	len;
	size_t	i;

	player_found = 0;
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		exitPerror("MAP", fd);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		player_found += find_player(data, line, i);
		len = ft_strlen(line);
		if (line[len - 1] == '\n')
			len--;
		ft_memcpy(data->map.map + i, line, len);
		while (len < data->map.width)
		{
			data->map.map[i + len] = ' ';
			len++;
		}
		free(line);
		if (player_found > 1)
			exitError("More than one player present on the map\n", 1);
		line = get_next_line(fd);
		i += data->map.width;
	}
	if (!player_found)
		exitError("Could not find a player's start position\n", 1);
}

static void	check_map(t_data *data)
{
	char	*map;
	size_t	height;
	size_t	width;
	size_t	i;

	map = data->map.map;
	height = data->map.height;
	width = data->map.width;
	i = 0;
	while (i < height * width)
	{
		if (!ft_strchr("01 ", map[i]))
			exitError("Undefined charachter\n", 1);
		if (map[i] == '0')
		{
			if (i < width || i > (height - 1) * width ||
				i % width == 0 || i % width == width - 1 ||
				map[i + 1] == ' ' || map[i - 1] == ' ' ||
				map[i + width] == ' ' || map[i - width] == ' ')
				exitError("Map not closed\n", 1);
		}
		i++;
	}
}

void	initData(char *map_name, t_data *data)
{
	int		fd;
	char	*line;

	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		exitPerror("MAP", fd);
	line = get_next_line(fd);
	if (line == NULL)
		exitError("Could not read map\n", 1);
	data->keys.keys_pressed_count = 0;
	get_dimensions(line, data, fd);
	data->mlx_data.img.img = mlx_new_image(
			data->mlx_data.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->mlx_data.img.addr = mlx_get_data_addr(
			data->mlx_data.img.img, &data->mlx_data.img.bits_per_pixel,
			&data->mlx_data.img.line_len, &data->mlx_data.img.endian);
	data->map.map = malloc((data->map.height * data->map.width) * sizeof(char));
	if (data->map.map == NULL)
		return ;
	fill_map(map_name, data, fd);
	check_map(data);
	fd = close(fd);
	if (fd)
		exitPerror("CLOSE", fd);
}

//Called when pressing window close
static int	exit_program()
{
	exit(0);
}

void	initLoop(void *mlx_ptr, void *win_ptr, t_data *data)
{
	mlx_hook(win_ptr, KeyPress, KeyPressMask, keyPressHook, &data->keys);
	mlx_hook(win_ptr, KeyRelease, KeyReleaseMask, keyReleaseHook, &data->keys);
	mlx_hook(win_ptr, DestroyNotify, 0, exit_program, NULL);
	mlx_loop_hook(mlx_ptr, mainLoop, data);
	mlx_loop(mlx_ptr);
}
