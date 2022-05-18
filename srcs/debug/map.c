/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:52:54 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/18 00:57:42 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	print_map(t_map *map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			printf("%c", map->map[j + i * map->width]);
			++j;
		}
		printf("$ (%li)\n", i);
		++i;
	}
}
