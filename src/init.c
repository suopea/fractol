/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuopea <ssuopea@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:06:27 by ssuopea           #+#    #+#             */
/*   Updated: 2025/08/22 17:37:35 by ssuopea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "fractal.h"

int	initialize(t_data *data)
{
	data->px = malloc(WIDTH * HEIGHT * sizeof(t_complex));
	if (!data->px)
		return (0);
	data->orbits = malloc(WIDTH * HEIGHT * sizeof(t_complex));
	if (!data->orbits)
	{
		free(data->px);
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
