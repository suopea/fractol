/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuopea <ssuopea@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:06:27 by ssuopea           #+#    #+#             */
/*   Updated: 2025/08/23 13:45:00 by ssuopea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "fractal.h"

int	initialize_program(t_data *data)
{
	data->width = WIDTH;
	data->height = HEIGHT;
	data->px_count = data->width * data->height;
	data->work_per_frame = DEFAULT_WORK_PER_FRAME;
	allocate_everything(data);
	reset(data);
	return (1);
}

void	free_and_exit(t_data *data)
{
	free_everything(data);
	if (data->frame)
		mlx_delete_image(data->mlx, data->frame);
	mlx_close_window(data->mlx);
}

void	allocate_everything(t_data *data)
{
	data->px = malloc(data->px_count * sizeof(t_complex));
	if (!data->px)
		free_and_exit(data);
	data->orbits = malloc(data->px_count * sizeof(t_complex));
	if (!data->orbits)
		free_and_exit(data);
	data->escape_times = calloc(data->px_count, sizeof(int));
	if (!data->escape_times)
		free_and_exit(data);
}

void	reset(t_data *data)
{
	data->paused = false;
	data->resizing = 0;
	data->px_count = data->width * data->height;
	bzero(data->escape_times, data->px_count);
	data->scale = DEFAULT_SCALE;
	data->location.i = 0;
	data->location.r = 0;
	data->iteration = 0;
	update_origins(data);
	move_center(data, 0, 0);
}

int initialize_mlx(t_data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "fractol", true);
	if (!data->mlx)
		return (0);
	data->frame = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->frame
		|| mlx_image_to_window(data->mlx, data->frame, 0, 0) < 0)
		return (0);
	return (1);
}

void	free_everything(t_data *data)
{
	if (data->escape_times)
	{
		free(data->escape_times);
		data->escape_times = NULL;
	}
	if (data->orbits)
	{
		free(data->orbits);
		data->orbits = NULL;
	}
	if (data->px)
	{
		free(data->px);
		data->px = NULL;
	}
}
