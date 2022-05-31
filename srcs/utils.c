/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 10:17:42 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/31 14:32:09 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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

int	str_isspace(char *str)
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
