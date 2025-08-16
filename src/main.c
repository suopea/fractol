/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuopea <ssuopea@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:52:50 by ssuopea           #+#    #+#             */
/*   Updated: 2025/08/14 17:05:06 by ssuopea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "fractal.h"
#include <string.h>
#include <stdio.h>

void	increment_pixel(uint8_t *pixel)
{
	pixel[0]++;
	// pixel[1]++;
	// pixel[2]++;
}

void	print_cursor_coordinates(t_data *data)
{
	int32_t x;
	int32_t y;

	mlx_get_mouse_pos(data->mlx, &x, &y);	
	printf("%i, %i\n", x, y);
}

void	loop_hook(void *input)
{
	t_data	*data = input;
	(void)data;
	print_cursor_coordinates(data);
}

void	set_alpha(uint8_t *pixels)
{
	int i = 0;

	while (i < WIDTH * HEIGHT)
	{
		pixels[i * 4 + 3] = 0xFF;
		pixels[i * 4 + 0] = i;
		// pixels[i * 4 + 1] = i;
		// pixels[i * 4 + 2] = i;
		i++;
	}
}

t_complex	index_to_point(int index)
{
	
}

void	initialize(t_data *data)
{
	data->scale = START_SCALE;
}

int main(void)
{
	t_data	data;

	data.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	data.live_frame = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	bzero(data.live_frame->pixels, WIDTH * HEIGHT * sizeof(int32_t));
	set_alpha(data.live_frame->pixels);
	// gradient(data.live_frame);
	if (mlx_image_to_window(data.mlx, data.live_frame, 0, 0) == -1)
	{
		mlx_close_window(data.mlx);
		return(1);
	}
	mlx_loop_hook(data.mlx, &loop_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}

