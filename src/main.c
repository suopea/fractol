/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuopea <ssuopea@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:52:50 by ssuopea           #+#    #+#             */
/*   Updated: 2025/08/27 16:06:33 by ssuopea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "fractal.h"

static void	loop_hook(void *input);
static int	initialize(t_data *data, int argc, char **argv);

int main(int argc, char **argv)
{
	t_data	data;

	if (argc < 2)
		exit (1);
	if (!strcmp(argv[1], "julia"))
		data.type = julia;
	else
		data.type = mandelbrot;
	initialize(&data, argc, argv);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}

int	initialize(t_data *data, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	if (!initialize_program(data))
		exit(1);
	if (!initialize_mlx(data))
	{
		mlx_terminate(data->mlx);
		exit(1);
	}
	if (data->type == julia)
	{
		data->c.r = strtod(argv[2], NULL);
		data->c.i = strtod(argv[3], NULL);
	}
	mlx_mouse_hook(data->mlx, mouse_hook, data);
	mlx_scroll_hook(data->mlx, scroll_hook, data);
	mlx_resize_hook(data->mlx, resize_hook, data);
	mlx_loop_hook(data->mlx, loop_hook, data);
	mlx_key_hook(data->mlx, key_hook, data);
	reset(data);
	return (1);
}

#include <stdio.h>
#include <unistd.h>
static void	update_title(t_data *data)
{
	int32_t x;
	int32_t y;
	char	*string;

	string = malloc(1000);
	mlx_get_mouse_pos(data->mlx, &x, &y);	
	sprintf(string, "location %.5f, %.5f | scale: %e | iter: %i | wait: %i", 
		 data->location.r, data->location.i, data->scale,
		 data->iteration, data->wait);
	mlx_set_window_title(data->mlx, string);
	free(string);
}

static void	loop_hook(void *input)
{
	t_data	*data;
	int		i;

	data = input;
	if (data->paused)
		return ;
	if (about_to_resize(data))
		return ;
	update_title(data);
	if (!data->all_black)
	{
		i = 0;
		while (i < data->work_per_frame)
		{
			iterate_once(data);
			i++;
		}
		usleep(data->wait);
	}
	else
		iterate_until_first_escape(data);
	color_pixels(data);
	if (data->waiting_to_zoom)
	{
		if (data->waiting_to_zoom < ZOOM_WAIT)
		{
			draw_zoom_box(data);
			data->waiting_to_zoom++;
		}
		else
		{
			get_cursor_location_and_zoom(data, data->to_zoom_soon);
			data->to_zoom_soon = 1;
		}
	}
	draw_cursor_cross(data);
}

