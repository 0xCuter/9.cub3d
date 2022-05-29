/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:55:51 by scuter            #+#    #+#             */
/*   Updated: 2022/05/27 10:35:40 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

//Parses the texture file path in the config data structure
void	parse_texture(char *line, int id, int fd, t_data *data)
{
	char	*str;
	if (str_isspace(line))
		exit_close_error("Texture path is empty\n", 1, fd);
	str = ft_strtrim(line, SPACES);
	check_ext(str, "xpm", fd);
	data->config.texture[id] = ft_strdup(str);
	free(str);
}

//Checks if the RGB value is in the right format
static char	check_format(char *line)
{
	int	commas;
	int	i;

	commas = 0;
	i = 0;
	while (line[i])
	{
		if (ft_isdigit(line[i]) || line[i] == ',')
		{
			if (line[i] == ',')
				commas++;
		}
		else
			return (1);
		i++;
	}
	if (commas != 2)
		return (1);
	return (0);
}

//Parses the texture file path in the config data structure
void	parse_color(char *line, int id, int fd, t_data *data)
{
	char	*str;
	char	**split;
	int		color[3];

	if (str_isspace(line))
		exit_close_error("RGB value is empty\n", 1, fd);
	str = ft_strtrim(line, SPACES);
	if (check_format(str))
		exit_close_error("RGB format is invalid\n", 1, fd);
	split = ft_split(str, ',');
	free(str);
	color[0] = ft_atoi(split[0]);
	color[1] = ft_atoi(split[1]);
	color[2] = ft_atoi(split[2]);
	free(split);
	if ((color[0] < 0 || color[0] > 255) ||
		(color[1] < 0 || color[1] > 255) ||
		(color[2] < 0 || color[2] > 255))
		exit_close_error("RGB value is out of range\n", 1, fd);
	data->config.color[id] = argb(0, (unsigned char)color[0],
	(unsigned char)color[1], (unsigned char)color[2]);
}
