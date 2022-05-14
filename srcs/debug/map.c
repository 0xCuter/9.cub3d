/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:52:54 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/11 15:57:19 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	print_map(t_map *map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < map->len)
	{
		j = 0;
		while (j < map->len)
		{
			printf("%c", map->map[j + i * map->len]);
			++j;
		}
		printf("$ (%li)\n", i);
		++i;
	}
}
