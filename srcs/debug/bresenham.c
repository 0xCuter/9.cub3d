/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 09:49:44 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/20 12:01:02 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

// draw_line subfunction
static void	plot_line_low(t_img *img, t_point *p, t_point d_p, int c)
{
	t_point	current_p;
	int		d;
	int		yi;

	current_p = (t_point){p[0].x, p[0].y};
	yi = 1;
	if (d_p.y < 0)
	{
		yi = -1;
		d_p.y = -d_p.y;
	}
	d = 2 * d_p.y - d_p.x;
	while (current_p.x <= p[1].x)
	{
		imgPixelPut(img, c, current_p);
		if (d > 0)
		{
			current_p.y += yi;
			d += 2 * (d_p.y - d_p.x);
		}
		else
			d = d + 2 * d_p.y;
		current_p.x += 1;
	}
}

// draw_line subfunction
static void	plot_line_high(t_img *img, t_point *p, t_point d_p, int c)
{
	t_point	current_p;
	int		d;
	int		xi;

	current_p = (t_point){p[0].x, p[0].y};
	xi = 1;
	if (d_p.x < 0)
	{
		xi = -1;
		d_p.x = -d_p.x;
	}
	d = 2 * d_p.x - d_p.y;
	while (current_p.y <= p[1].y)
	{
		imgPixelPut(img, c, current_p);
		if (d > 0)
		{
			current_p.x += xi;
			d += 2 * (d_p.x - d_p.y);
		}
		else
			d = d + 2 * d_p.x;
		current_p.y += 1;
	}
}

// Draws a "color" line of between two points using Bresenham's line algorithm
void	drawLine(t_img *img, int c, t_point p1, t_point p2)
{
	t_point	p[2];
	t_point	p_reversed[2];
	t_point	d_p;
	t_point	d_p_reversed;

	p[0] = (t_point){p1.x, p1.y};
	p[1] = (t_point){p2.x, p2.y};
	p_reversed[0] = (t_point){p2.x, p2.y};
	p_reversed[1] = (t_point){p1.x, p1.y};
	d_p.x = p2.x - p1.x;
	d_p_reversed.x = p_reversed[1].x - p_reversed[0].x;
	d_p.y = p2.y - p1.y;
	d_p_reversed.y = p_reversed[1].y - p_reversed[0].y;
	if (abs(d_p.y) < abs(d_p.x))
	{
		if (p1.x > p2.x)
			plot_line_low(img, p_reversed, d_p_reversed, c);
		else
			plot_line_low(img, p, d_p, c);
	}
	else
	{
		if (p1.y > p2.y)
			plot_line_high(img, p_reversed, d_p_reversed, c);
		else
			plot_line_high(img, p, d_p, c);
	}
}
