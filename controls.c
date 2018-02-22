/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubrovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 14:58:42 by mdubrovs          #+#    #+#             */
/*   Updated: 2017/03/04 17:57:40 by mdubrovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	scale(int button, int x, int y, t_viewport *v)
{
	if (button == SCROLL_DOWN)
	{
		x -= WIN_W / 2;
		y -= WIN_H / 2;
		v->scale *= 1.1;
		v->x_shift += x / v->scale / 1.5;
		v->y_shift -= y / v->scale / 1.5;
	}
	else if (button == SCROLL_UP)
		v->scale /= 1.2;
	else if (button == MOUSE_L)
		v->z_max = (int)(v->z_max * 1.1) == v->z_max ? v->z_max + 1 :
			v->z_max * 1.1;
	else if (button == MOUSE_R && v->z_max > 2.0)
		v->z_max = (int)(v->z_max / 1.1) == v->z_max ? v->z_max - 1 :
			v->z_max / 1.1;
}

int			mouse_hook(int button, int x, int y, t_viewport *v)
{
	scale(button, x, y, v);
	reload(v);
	return (0);
}

int			mouse_move_hook(int x, int y, t_viewport *v)
{
	if (!v->pause)
	{
		x -= WIN_W / 2;
		y -= WIN_H / 2;
		v->theta = ((float)x / WIN_W) * 0.84;
		v->phi = ((float)y / WIN_H) * 0.84;
		reload(v);
	}
	return (0);
}

void		reset(t_viewport *v)
{
	v->scale = 1.0;
	v->z_max = 84;
	v->x_shift = 0.0;
	v->y_shift = 0.0;
}

int			kbrd_hook(int keycode, t_viewport *v)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(v->mlx, v->win);
		exit(0);
	}
	else if (keycode == KEY_PAUSE)
		v->pause = !v->pause;
	else if (keycode == KEY_UP)
		v->y_shift += (WIN_H / 15.0) / v->scale;
	else if (keycode == KEY_DOWN)
		v->y_shift -= (WIN_H / 15.0) / v->scale;
	else if (keycode == KEY_LEFT)
		v->x_shift -= (WIN_W / 15.0) / v->scale;
	else if (keycode == KEY_RIGHT)
		v->x_shift += (WIN_W / 15.0) / v->scale;
	else if (keycode == KEY_R)
		reset(v);
	else if (keycode == 116)
		v->col_seed = (v->col_seed != 124) ? v->col_seed + 4 : 0;
	else if (keycode == 121)
		v->col_seed = (v->col_seed != 0) ? v->col_seed - 4 : 124;
	reload(v);
	return (0);
}
