/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 10:17:42 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/24 10:46:17 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	exitPerror(char *s, int i)
{
	perror(s);
	exit(i);
}

void	exitError(char *s, int i)
{
	ft_putstr_fd(s, STDERR_FILENO);
	exit(i);
}

void	fixAngle(double *angle)
{
	if (*angle < 0)
		*angle += 2 * M_PI;
	if (*angle >= 2 * M_PI)
		*angle -= 2 * M_PI;
}
