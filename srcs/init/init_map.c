/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:44:31 by vvandenb          #+#    #+#             */
/*   Updated: 2022/06/01 02:07:30 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

//Reads the config file until the first line of the map
static char	*go_to_map(int fd)
{
	char	*line;
	int		i;

	line = get_next_line(fd);
	i = 0;
	while (line)
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

static char	fill_str(char *line, t_data *data, size_t i)
{
	size_t	len;

	len = ft_strlen(line);
	if (len < 2)
	{
		free(line);
		return (1);
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
	return (0);
}

//Inits a `t_map` structure
static void	fill_map(char *line, t_data *data, int fd)
{
	char	player_found;
	size_t	i;

	player_found = 0;
	i = 0;
	while (line)
	{
		player_found += init_player(data, line, i);
		if (fill_str(line, data, i))
			break ;
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
			if (i < width || i > (height - 1) * width \
				|| i % width == 0 || i % width == width - 1 \
				|| map[i + 1] == ' ' || map[i - 1] == ' ' \
				|| map[i + width] == ' ' || map[i - width] == ' ')
				exit_error("Map not closed\n", 1);
		}
		i++;
	}
}

//Initializes the map data structure
void	init_map(t_data *data, char *line, int fd, char *map_name)
{
	init_dimensions(line, &data->map, fd);
	safe_close(fd);
	data->map.map = malloc((data->map.height * data->map.width) * sizeof(char));
	if (data->map.map == NULL)
		exit_error("Malloc error\n", 1);
	fd = safe_open(map_name, O_RDONLY);
	line = go_to_map(fd);
	fill_map(line, data, fd);
	check_map(data);
	safe_close(fd);
}
