/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuopea <ssuopea@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:52:50 by ssuopea           #+#    #+#             */
/*   Updated: 2025/08/23 13:49:30 by ssuopea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "fractal.h"

static void	loop_mandelbrot(void *input);
static int	initialize_mandelbrot(t_data *data, int argc, char **argv);
static int initialize_julia(t_data *data, int argc, char **argv);
static void	loop_julia(void *input);

int main(int argc, char **argv)
{
	t_data	data;

	if (argc < 2)
		exit (1);
	if (!strcmp(argv[1], "julia"))
		initialize_julia(&data, argc, argv);
	else if (!strcmp(argv[1], "mandelbrot"))
		initialize_mandelbrot(&data, argc, argv);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}

int	initialize_mandelbrot(t_data *data, int argc, char **argv)
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
	data->type = mandelbrot;
	mlx_mouse_hook(data->mlx, mouse_hook, data);
	mlx_scroll_hook(data->mlx, scroll_hook, data);
	mlx_resize_hook(data->mlx, resize_hook, data);
	mlx_loop_hook(data->mlx, loop_mandelbrot, data);
	mlx_key_hook(data->mlx, key_hook, data);
	reset_mandelbrot(data);
	return (1);
}

int initialize_julia(t_data *data, int argc, char **argv)
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
	data->type = julia;
	data->c.r = strtod(argv[2], NULL);
	data->c.i = strtod(argv[3], NULL);
	mlx_mouse_hook(data->mlx, mouse_hook, data);
	mlx_scroll_hook(data->mlx, scroll_hook, data);
	mlx_resize_hook(data->mlx, resize_hook, data);
	mlx_loop_hook(data->mlx, loop_julia, data);
	mlx_key_hook(data->mlx, key_hook, data);
	reset_julia(data);
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

static void	loop_mandelbrot(void *input)
{
	t_data	*data;
	int		i;

	data = input;
	if (data->paused)
		return ;
	if (about_to_resize(data))
		return ;
	update_title(data);
	while (data->all_black)
		iterate_until_first_escape(data);
	i = 0;
	while (i < data->work_per_frame)
	{
		iterate_once(data);
		i++;
	}
	colorize_pixels(data);
	usleep(data->wait);
}

static void	loop_julia(void *input)
{
	t_data	*data;
	int		i;

	data = input;
	if (data->paused)
		return ;
	if (about_to_resize(data))
		return ;
	update_title(data);
	// while (data->all_black)
	// 	iterate_until_first_escape(data);
	i = 0;
	while (i < data->work_per_frame)
	{
		iterate_once(data);
		i++;
	}
	colorize_pixels(data);
	usleep(data->wait);
}
