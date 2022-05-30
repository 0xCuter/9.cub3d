/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:44:31 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/30 15:16:28 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

//Gets the dimensions of the map from the config file
static void	get_map_dimensions(char *line, t_map *map, int fd)
{
	size_t	max_len;
	size_t	len;
	size_t	i;

	max_len = 0;
	i = 0;
	while (line)
	{
		len = ft_strlen(line);
		if (len < 2)
		{
			free(line);
			break ;
		}
		if (line[len - 1] == '\n')
			len--;
		if (len > max_len)
			max_len = len;
		free(line);
		line = get_next_line(fd);
		i++;
	}
	map->width = max_len;
	map->height = i;
}

//Reads the config file until the first line of the map
static char	*go_to_map(int fd)
{
	char	*line;
	int		i;

	line = get_next_line(fd);
	i = 0;
	while(line)
	{
		if (!str_isspace(line))
		{
			while (ft_strchr(SPACES, line[i]))
				i++;
			if (ft_strchr("01", line[i]))
				return (line);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (NULL);
}

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
		data->player.pos = (t_fpoint){player - line + 0.5, i / data->map.width + 0.5};
		*player = '0';
		return (1);
	}
	return (0);
}

//Inits a `t_map` structure
static void	fill_map(char *line, t_data *data, int fd)
{
	char	player_found;
	size_t	len;
	size_t	i;

	player_found = 0;
	i = 0;
	while (line)
	{
		player_found += find_player(data, line, i);
		len = ft_strlen(line);
		if (len < 2)
		{
			free(line);
			break ;
		}
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
			exit_close_error("More than one player present on the map\n", 1, fd);
		line = get_next_line(fd);
		i += data->map.width;
	}
	if (!player_found)
		exit_close_error("Could not find a player's start position\n", 1, fd);
}

//Checks that the map respects all the rules
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
			exit_error("Undefined character\n", 1);
		if (map[i] == '0')
		{
			if (i < width || i > (height - 1) * width ||
				i % width == 0 || i % width == width - 1 ||
				map[i + 1] == ' ' || map[i - 1] == ' ' ||
				map[i + width] == ' ' || map[i - width] == ' ')
				exit_error("Map not closed\n", 1);
		}
		i++;
	}
}

//Initializes the map data structure
void	init_map(t_data *data, char *line, int fd, char *map_name)
{
	get_map_dimensions(line, &data->map, fd);
	safe_close(fd);
	data->map.map = malloc((data->map.height * data->map.width) * sizeof(char));
	if (&data->map.map == NULL)
		exit_error("Malloc error\n", 1);
	fd = safe_open(map_name, O_RDONLY);
	line = go_to_map(fd);
	fill_map(line, data, fd);
	check_map(data);
	safe_close(fd);
}
