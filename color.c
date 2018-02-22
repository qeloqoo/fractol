/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubrovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:47:42 by mdubrovs          #+#    #+#             */
/*   Updated: 2017/03/04 17:45:31 by mdubrovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_color_array(t_viewport *v, int col_max)
{
	int				i;
	float			f;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	v->colors = (int*)ft_memalloc(sizeof(int) * col_max);
	f = 0;
	i = -1;
	while (++i < col_max)
	{
		r = (unsigned char)((-cos(f) + 1.0) * 127.0);
		g = (unsigned char)((sin(f) + 1.0) * 127.0);
		b = (unsigned char)((cos(f) + 1.0) * 127.0);
		v->colors[i] = ((int)r) << 16 | ((int)g) << 8 | b;
		f += 2 * M_PI / col_max;
	}
}

void	color_pixel(t_viewport *v, int x, int y, int iter)
{
	int	byte;
	int	col;

	if (iter != v->z_max)
		col = v->colors[(iter + v->col_seed) % v->col_max];
	else
		col = 0;
	byte = (x * 4) + (y * v->size_line);
	v->pxls[byte] = col;
	v->pxls[++byte] = col >> 8;
	v->pxls[++byte] = col >> 16;
}
