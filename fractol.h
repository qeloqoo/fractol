/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubrovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 15:14:20 by mdubrovs          #+#    #+#             */
/*   Updated: 2017/03/04 18:24:39 by mdubrovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft/libft.h"
# include "minilibx/mlx.h"
# include <math.h>
# include <pthread.h>

# define WIN_W 800
# define WIN_H 600

# define KEY_ESC 53
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_PLUS 69
# define KEY_MINUS 78
# define KEY_PAUSE 49
# define KEY_R 15

# define MOUSE_L 1
# define MOUSE_R 2
# define SCROLL_UP 4
# define SCROLL_DOWN 5

typedef struct	s_viewport
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*pxls;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	int			(*fractal)(struct s_viewport*, long double, long double);
	int			*colors;
	int			col_max;
	int			col_seed;
	int			width;
	int			height;
	int			z_max;
	long double	scale;
	long double	x_shift;
	long double y_shift;
	float		theta;
	float		phi;
	char		pause;

}				t_viewport;

typedef struct	s_grid
{
	int			x_begin;
	int			x_end;
	int			y_begin;
	int			y_end;
	t_viewport	*view;
	pthread_t	thread;
}				t_grid;

void			init_viewport(t_viewport *v, char *str);
void			reload(t_viewport *v);
int				kbrd_hook(int keycode, t_viewport *v);
int				frac_mandelbrot(t_viewport *v, long double r, long double im);
int				frac_burning_ship(t_viewport *v, long double r, long double im);
int				frac_julia(t_viewport *v, long double r, long double im);
int				frac_spider(t_viewport *v, long double r, long double im);
int				frac_sierpinski(t_viewport *v, long double x, long double y);
int				frac_test(t_viewport *v, long double r, long double im);
void			init_color_array(t_viewport *v, int col_max);
void			color_pixel(t_viewport *v, int x, int y, int iter);
int				mouse_hook(int button, int x, int y, t_viewport *v);
int				mouse_move_hook(int x, int y, t_viewport *v);

#endif
