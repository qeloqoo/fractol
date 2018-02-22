/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubrovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 15:06:54 by mdubrovs          #+#    #+#             */
/*   Updated: 2017/03/04 18:22:36 by mdubrovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	frac_mandelbrot(t_viewport *v, long double r, long double im)
{
	long double x;
	long double y;
	long double t;
	int			i;

	r = ((3.0 * r / WIN_W - 2.0) / v->scale) + (v->x_shift / WIN_W);
	im = ((-2.0 * im / WIN_H + 1.0) / v->scale) + (v->y_shift / WIN_H);
	x = 0;
	y = 0;
	i = -1;
	while ((++i < v->z_max) && (x * x + y * y <= 4.0))
	{
		t = x * x - y * y + r;
		y = 2 * x * y + im;
		x = t;
	}
	return (i);
}

int	frac_burning_ship(t_viewport *v, long double r, long double im)
{
	long double	x;
	long double	y;
	long double	xt;
	long double	yt;
	int			i;

	r = ((4.0 * r / WIN_W - 2.0) / v->scale) + (v->x_shift / WIN_W);
	im = ((-4.0 * (1 - im / WIN_H) + 2.0) / v->scale) - (v->y_shift / WIN_H);
	x = 0;
	y = 0;
	i = -1;
	while (x * x + y * y <= 4.0 && ++i < v->z_max)
	{
		xt = fabsl(x) * fabsl(x) - fabsl(y) * fabsl(y) + r;
		yt = 2 * fabsl(x) * fabsl(y) + im;
		if (x == xt && y == yt)
		{
			i = v->z_max;
			break ;
		}
		x = xt;
		y = yt;
	}
	return (i);
}

int	frac_julia(t_viewport *v, long double r, long double im)
{
	long double	t;
	int			i;

	r = ((4 * r / WIN_W - 2.0) / v->scale) + ((v->x_shift / WIN_W));
	im = ((-3 * im / WIN_H + 1.5) / v->scale) + ((v->y_shift / WIN_H));
	i = -1;
	while ((++i < v->z_max) && (r * r + im * im <= 4.0))
	{
		t = r;
		r = r * r - im * im + v->theta;
		im = 2 * t * im + v->phi;
	}
	return (i);
}

int	frac_spider(t_viewport *v, long double r, long double im)
{
	long double x;
	long double y;
	long double t;
	int			i;

	r = ((3.0 * r / WIN_W - 2.0) / v->scale) + (v->x_shift / WIN_W);
	im = ((-3.0 * im / WIN_H + 1.5) / v->scale) + (v->y_shift / WIN_H);
	x = 0;
	y = 0;
	i = -1;
	while ((++i < v->z_max) && (x * x + y * y <= 4.0))
	{
		t = x * x - y * y + r;
		y = 2 * x * y + im;
		x = t;
		r = r / 2 + x;
		im = im / 2 + y;
	}
	return (i);
}

int	frac_sierpinski(t_viewport *v, long double x, long double y)
{
	int			i;

	x = ((4 * x / WIN_W - 2.0) / v->scale) + ((v->x_shift / WIN_W));
	y = ((-3 * y / WIN_H + 1) / v->scale) + ((v->y_shift / WIN_H));
	i = -1;
	while ((++i < v->z_max) && (x * x + y * y <= 4.0))
	{
		if (y > .5)
		{
			x *= 2;
			y = 2 * y - 1;
		}
		else if (x > .5)
		{
			x = 2 * x - 1;
			y *= 2;
		}
		else
		{
			x *= 2;
			y *= 2;
		}
	}
	return (i);
}
