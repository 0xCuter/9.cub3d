/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dimensions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 01:59:46 by scuter            #+#    #+#             */
/*   Updated: 2022/06/01 02:02:39 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

//Gets the dimensions of the map from the config file
void	init_dimensions(char *line, t_map *map, int fd)
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
