/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 10:17:42 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/24 18:13:03 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	fix_angle(double *angle)
{
	if (*angle < 0)
		*angle += 2 * M_PI;
	if (*angle >= 2 * M_PI)
		*angle -= 2 * M_PI;
}

int	safe_open(char *file_name, int flags)
{
	int	fd;

	fd = open(file_name, flags);
	if (fd < 0)
		exit_perror(file_name, fd);
	return (fd);
}

void	safe_close(int fd)
{
	if (close(fd))
		exit_perror("CLOSE", fd);
}
