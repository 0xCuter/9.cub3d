/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 10:17:42 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/24 11:00:52 by vvandenb         ###   ########.fr       */
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

void	fix_angle(double *angle)
{
	if (*angle < 0)
		*angle += 2 * M_PI;
	if (*angle >= 2 * M_PI)
		*angle -= 2 * M_PI;
}
