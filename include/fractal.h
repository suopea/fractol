/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuopea <ssuopea@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 12:47:25 by ssuopea           #+#    #+#             */
/*   Updated: 2025/08/27 16:27:20 by ssuopea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_H
# define FRACTAL_H
# include <math.h>
# include <stdint.h>
# include <stdbool.h>
# include <stdlib.h>
# include "MLX42/MLX42.h"
# define WIDTH 4000
# define HEIGHT 2000
# define DEFAULT_SCALE 0.005
# define DEFAULT_WORK_PER_FRAME 1
# define DEFAULT_SPEED 1
# define SPEED_CHANGE 5000
# define MEGAZOOM 0.01
# define ZOOM_WAIT 15
# define RESIZE_WAIT 10
# define SCROLL_AMOUNT 1.1
# define KEY_ESC MLX_KEY_ESCAPE
# define KEY_REITERATE MLX_KEY_I
# define KEY_RESET MLX_KEY_R
# define BOX_COLOR 0x88888800
# define CURSOR_COLOR 0x55555500
# define CURSOR_FADE 20


// illegal
# include <string.h>
# include <stdio.h>

typedef enum
{
	mandelbrot,
	julia,
}	e_fractal;

typedef struct s_complex
{
	double	r;
	double	i;
}	t_complex;

typedef struct s_data
{
	t_complex		*px;
	int				px_count;
	t_complex		c;
	t_complex		*orbits;
	int				*escape_times;
	mlx_image_t		*frame;
	double			scale;
	double			to_zoom_soon;
	int				waiting_to_zoom;
	int				iteration;
	t_complex		location;
	int				work_per_frame;			
	mlx_t			*mlx;
	int				width;
	int				height;
	int				new_width;
	int				new_height;
	int				new_px_count;
	bool			paused;
	int				resizing;
	int				wait;
	bool			all_black;
	e_fractal		type;
	bool			cursor_visible;
	int				mouse_last_position;
	int				cursor_fading;
}	t_data;

void	update_locations(t_data *data);
void	reset_orbits(t_data *data);
void	new_location_from_center(t_data *data, int x, int y);
void	zoom_to_point(t_data *data, int x, int y, float change);
void	draw_zoom_box(t_data *data);
void	get_cursor_location_and_zoom(t_data *data, float zoom_amount);
int		initialize_program(t_data *data);
int		initialize_mlx(t_data *data);
void	allocate_everything(t_data *data);
void	reset(t_data *data);
int		about_to_resize(t_data *data);
void	clear_screen(t_data *data);
void	scroll_hook(double xdelta, double ydelta, void *input);
void	key_hook(mlx_key_data_t keydata, void *input);
void	resize_hook(int32_t width, int32_t height, void *input);
void	iterate_once(t_data *data);
void	iterate_julia_once(t_data *data);
void	iterate_until_first_escape(t_data *data);
void	color_pixels(t_data *data);
int		center(t_data *data);
int		i(int x, int y, t_data *data);
int		x(int i, t_data *data);
int		y(int i, t_data *data);
int32_t	get_pixel_color(uint8_t *pixels, int i);
void	draw_cursor_cross(t_data *data);
void	free_everything(t_data *data);
void	free_and_exit(t_data *data);
void	mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods, void *input);

#endif
