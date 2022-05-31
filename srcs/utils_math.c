/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:31:41 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/31 14:33:15 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

float	distance(t_fpoint *p1, t_fpoint *p2)
{
	return (sqrt((p1->y - p2->y) * (p1->y - p2->y)
			+ (p1->x - p2->x) * (p1->x - p2->x)));
}

void	fix_angle(float *angle)
{
	if (*angle < 0)
		*angle += 2 * M_PI;
	if (*angle >= 2 * M_PI)
		*angle -= 2 * M_PI;
}
