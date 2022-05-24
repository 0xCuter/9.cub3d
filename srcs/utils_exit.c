/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 18:05:29 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/24 18:13:16 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	exit_perror(char *s, int i)
{
	perror(s);
	exit(i);
}

void	exit_error(char *s, int i)
{
	ft_putstr_fd(s, STDERR_FILENO);
	exit(i);
}

void	exit_close_error(char *s, int i, int fd)
{
	safe_close(fd);
	ft_putstr_fd(s, STDERR_FILENO);
	exit(i);
}
