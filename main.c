/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubrovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 15:53:49 by mdubrovs          #+#    #+#             */
/*   Updated: 2017/03/04 17:44:43 by mdubrovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	errorexit(void)
{
	ft_putendl("Usage: ./fractol M/J/B/S/T [M/J/B/S/T]");
	ft_putendl("\tor [mandelbrot / julia / burning ship / spider / triangle]");
	exit(0);
}

static int	set_fractal(t_viewport *v, char *str)
{
	if (ft_strequ("M", str) || ft_strequ("mandelbrot", str))
		v->fractal = frac_mandelbrot;
	else if (ft_strequ("J", str) || ft_strequ("julia", str))
	{
		v->fractal = frac_julia;
		v->theta = -0.7;
		v->phi = 0.27015;
	}
	else if (ft_strequ("B", str) || ft_strequ("burning ship", str))
		v->fractal = frac_burning_ship;
	else if (ft_strequ("S", str) || ft_strequ("spider", str))
		v->fractal = frac_spider;
	else if (ft_strequ("T", str) || ft_strequ("triangle", str))
		v->fractal = frac_sierpinski;
	return (v->fractal == 0 ? 0 : 1);
}

int			main(int argc, char **argv)
{
	t_viewport	*view1;
	t_viewport	*view2;

	view1 = (t_viewport*)ft_memalloc(sizeof(t_viewport));
	view2 = (t_viewport*)ft_memalloc(sizeof(t_viewport));
	if (argc >= 2 && argc < 4)
	{
		view1->mlx = mlx_init();
		view2->mlx = view1->mlx;
		if (!set_fractal(view1, argv[1]))
			errorexit();
		if ((argc == 3) && (!set_fractal(view2, argv[2])))
			errorexit();
	}
	else
		errorexit();
	init_viewport(view1, argv[1]);
	reload(view1);
	if (argc == 3)
	{
		init_viewport(view2, argv[2]);
		reload(view2);
	}
	mlx_loop(view1->mlx);
}
