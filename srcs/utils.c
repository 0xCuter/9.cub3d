/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 10:17:42 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/26 21:31:17 by scuter           ###   ########.fr       */
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

int		str_isspace(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(SPACES, str[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
