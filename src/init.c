/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuopea <ssuopea@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:06:27 by ssuopea           #+#    #+#             */
/*   Updated: 2025/08/28 15:18:08 by ssuopea          ###   ########.fr       */
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
	data->to_zoom_soon = 1;
	data->waiting_to_zoom = 0;
	data->wait = DEFAULT_SPEED;
	data->mouse_last_position = 0;
	allocate_everything(data);
	return (1);
}

static void	locations_become_orbits(t_data *data)
{
	int	row;
	int	column;

	row = 0;
	while (row < data->height)
	{
		column = 0;
		while (column < data->width)
		{
			data->orbits[i(column, row, data)].r
				= data->location.r + row * data->scale;
			data->orbits[i(column, row, data)].i
				= data->location.i + column * data->scale;
			column++;
		}
		row++;
	}
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
	data->all_black = true;
	update_locations(data);
	new_location_from_center(data, 0, 0);
	if (data->type == julia)
		locations_become_orbits(data);
}

int	initialize_mlx(t_data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "fractol", true);
	if (!data->mlx)
		return (0);
	data->frame = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->frame
		|| mlx_image_to_window(data->mlx, data->frame, 0, 0) < 0)
		return (0);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	return (1);
}
