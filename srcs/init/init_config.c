/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 18:17:13 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/29 15:40:01 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

//Initializes the empty config data structure
static void	init_config(t_config *config)
{
	config->textures[0].img.img = NULL;
	config->textures[1].img.img = NULL;
	config->textures[2].img.img = NULL;
	config->textures[3].img.img = NULL;
	config->color[0] = 0;
	config->color[1] = 0;
}

//Checks if all the elements in the config file have been parsed before parsing the map
static char	check_if_ready(t_config *config, int fd)
{
	if (config->textures[0].img.img == NULL ||
		config->textures[1].img.img == NULL ||
		config->textures[2].img.img == NULL ||
		config->textures[3].img.img == NULL ||
		config->color[0] == 0 ||
		config->color[1] == 0)
		exit_close_error("Incomplete config file\n", 1, fd);
	return (1);
}

//Checks the line corresponding element and redirects the program accordingly
static char	parse_line(char *line, int fd, t_data *data)
{
	size_t	i;

	i = 0;
	if (str_isspace(line))
		return (0);
	while (ft_strchr(SPACES, line[i]))
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		parse_texture(&line[i + 3], 0, fd, data);
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		parse_texture(&line[i + 3], 1, fd, data);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		parse_texture(&line[i + 3], 2, fd, data);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		parse_texture(&line[i + 3], 3, fd, data);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		parse_color(&line[i + 2], 0, fd, data);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		parse_color(&line[i + 2], 1, fd, data);
	else if (line[i] == '0' || line[i] == '1')
		return (check_if_ready(&data->config, fd));
	else
		exit_close_error("Unrecognised element in config file\n", 1, fd);
	return (0);
}

char	*parse_config(t_data *data, char *line, int fd)
{
	init_config(&data->config);
	while (line)
	{
		if (parse_line(line, fd, data))
			return (line);
		free(line);
		line = get_next_line(fd);
	}
	return (NULL);
}
