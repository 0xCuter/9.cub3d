/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_infos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 18:17:13 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/24 18:57:51 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_infos(t_data *data, char *line, int fd)
{
	// char	*l_trimmed;
	// size_t	len;

	// while (line)
	// {
	// 	l_trimmed = ft_strtrim(line, " \t\n");
	// 	free(line);
	// 	if (l_trimmed && *l_trimmed)
	// 	{
	// 		printf("l_trimmed: %s$\n", l_trimmed);
	// 		len = ft_strlen(l_trimmed);
	// 		printf("len: %li$\n", len);
	// 	}
	// 	free(l_trimmed);
	// 	line = get_next_line(fd);
	// }
	(void)data;
	(void)line;
	(void)fd;
}
