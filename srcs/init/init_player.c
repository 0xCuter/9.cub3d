/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 01:42:27 by scuter            #+#    #+#             */
/*   Updated: 2022/06/01 02:08:30 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char	*get_player(char *line)
{
	char	*player;

	player = ft_strchr(line, 'N');
	if (player == NULL)
		player = ft_strchr(line, 'S');
	if (player == NULL)
		player = ft_strchr(line, 'W');
	if (player == NULL)
		player = ft_strchr(line, 'E');
	return (player);
}

//Inits player if it finds it in the map
char	init_player(t_data *data, char *line, int i)
{
	char	*player;

	player = get_player(line);
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
		data->player.pos = (t_fpoint){player - line + 0.5,
			i / data->map.width + 0.5};
		*player = '0';
		return (1);
	}
	return (0);
}
