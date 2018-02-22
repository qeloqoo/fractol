/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_procedures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubrovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:07:35 by mdubrovs          #+#    #+#             */
/*   Updated: 2017/03/04 18:21:11 by mdubrovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	*thread_handle(void *tmp)
{
	int		x;
	int		y;
	t_grid	*s;

	s = (t_grid*)tmp;
	y = s->y_begin - 1;
	while (++y < s->y_end)
	{
		x = s->x_begin - 1;
		while (++x < s->x_end)
			color_pixel(s->view, x, y, s->view->fractal(s->view, x, y));
	}
	return (NULL);
}

void	draw(t_viewport *v)
{
	t_grid	*grid;
	int		i;

	grid = (t_grid*)ft_memalloc(sizeof(t_grid) * 4);
	i = -1;
	while (++i < 4)
	{
		grid[i].x_begin = (WIN_W / 2) * (i % 2);
		grid[i].x_end = (WIN_W / 2) * (i % 2 + 1);
		grid[i].y_begin = (WIN_H / 2) * (i / 2);
		grid[i].y_end = (WIN_H / 2) * (i / 2 + 1);
		grid[i].view = v;
		pthread_create(&(grid[i].thread), NULL, thread_handle,
			(void*)&grid[i]);
	}
	i = -1;
	while (++i < 4)
		pthread_join(grid[i].thread, NULL);
	free(grid);
}

void	reload(t_viewport *v)
{
	v->img = mlx_new_image(v->mlx, WIN_W, WIN_H);
	v->pxls = mlx_get_data_addr(v->img, &(v->bits_per_pixel), &(v->size_line),
		&(v->endian));
	draw(v);
	mlx_put_image_to_window(v->mlx, v->win, v->img, 0, 0);
	mlx_string_put(v->mlx, v->win, 10, 5, 0xFFFFFF, ft_itoa(v->z_max));
	mlx_destroy_image(v->mlx, v->img);
}

int		expose(t_viewport *v)
{
	reload(v);
	return (0);
}

void	init_viewport(t_viewport *v, char *str)
{
	v->scale = 1.0;
	v->x_shift = 0.0;
	v->y_shift = 0.0;
	v->col_max = 126;
	v->col_seed = 0;
	v->z_max = 84;
	v->pause = 0;
	if (!v->theta)
	{
		v->theta = 0.0;
		v->phi = 0.0;
	}
	v->win = mlx_new_window(v->mlx, WIN_W, WIN_H, str);
	init_color_array(v, v->col_max);
	mlx_expose_hook(v->win, expose, v);
	mlx_hook(v->win, 2, 3, kbrd_hook, v);
	mlx_hook(v->win, 4, 5, mouse_hook, v);
	if (v->fractal == frac_julia)
		mlx_hook(v->win, 6, (1L << 6), mouse_move_hook, v);
}
