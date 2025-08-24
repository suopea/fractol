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

int	initialize(t_data *data)
{
	data->px_count = WIDTH * HEIGHT;
	data->px = malloc(data->px_count * sizeof(t_complex));
	if (!data->px)
		return (0);
	data->orbits = malloc(data->px_count * sizeof(t_complex));
	if (!data->orbits)
	{
		free(data->px);
		return (0);
	}
	data->escape_times = malloc(data->px_count * sizeof(int));
	if (!data->escape_times)
	{
		free(data->px);
		free(data->orbits);
		return (0);
	}
	data->scale = DEFAULT_SCALE;
	data->location.i = 0;
	data->location.r = 0;
	update_origins(data);
	move_center(data, 0, 0);
	data->iteration = 0;
	data->work_per_frame = DEFAULT_WORK_PER_FRAME;
	return (1);
}

int initialize_mlx(t_data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "fractol", false);
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
		free(data->escape_times);
	if (data->orbits)
		free(data->orbits);
	if (data->px)
		free(data->px);
	if (data->frame)
		mlx_delete_image(data->mlx, data->frame);
}
