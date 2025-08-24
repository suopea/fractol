/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuopea <ssuopea@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:52:50 by ssuopea           #+#    #+#             */
/*   Updated: 2025/08/24 10:49:39 by ssuopea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

static void	mandelbrot_loop(void *input);
static void	julia_loop(void *input);

int main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2 || !initialize(&data))
		return (1);
	if (!initialize_mlx(&data))
	{
		mlx_terminate(data.mlx);
		return (1);
	}
	mlx_mouse_hook(data.mlx, &mouse_hook, &data);
	mlx_scroll_hook(data.mlx, &scroll_hook, &data);
	mlx_key_hook(data.mlx, &key_hook, &data);
	if (!strcmp(argv[1], "julia"))
		mlx_loop_hook(data.mlx, &julia_loop, &data);
	if (!strcmp(argv[1], "mandelbrot"))
		mlx_loop_hook(data.mlx, &mandelbrot_loop, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}

static void	mandelbrot_loop(void *input)
{
	t_data	*data;
	int		i;

	data = input;
	i = 0;
	while (i < data->work_per_frame)
	{
		mandelbrot_once(data);
		i++;
	}
	colorize_pixels(data);
}

static void	julia_loop(void *input)
{
	t_data	*data;
	int		i;

	data = input;
	i = 0;
	while (i < data->work_per_frame)
	{
		julia_once(data);
		i++;
	}
	colorize_pixels(data);
}
