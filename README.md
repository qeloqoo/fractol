# fractol
Graphical educational project that introduces fractals and simple parallel calculations.
Unlike previous project (fdf), this one was more calculation intensive and required use of POSIX Threads for smooth display of graphics.

This project requires School 42 homebrew minilibX library (included) and was only tested in macOS El Capitan / Sierra environment.
Please, compile using Makefile (type 'make' in console while in project folder).

To launch program please use following syntax in console:
> ./fractol *

where * is either one of capital letters: **M**, **J**, **B**, **S**, **T** or one of fractal names: **mandelbrot**, **julia**, **burning ship**, **spider**, **triangle**

Typing
> ./fractol M "spider"

will launch 2 windows (allowed maximum) with mandelbrot and spider fractals respectively.

Controls:
- **Mouse scroll** zoomes in or out at location pointed by cursor
- **Mouse Left Click** increases amount of iterations (makes fractal more detailed)
- **Mouse Right Click** decreases amount of iterations (makes fractal less detailed)
- **Spaceba**r is used in Julia fractal and acts like a pause
- **Arrow Keys** shift picture in respective directions
- **R** resets fractal to initial state
- **PageUp / PageDown** scroll color pallete
- **ESC** exits program
