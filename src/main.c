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

#include "fractal.h"

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_randomize(void* param)
{
	(void)param;
	for (uint32_t i = 0; i < image->width; ++i)
	{
		for (uint32_t y = 0; y < image->height; ++y)
		{
			uint32_t color = ft_pixel(
				rand() % 0xFF, // R
				rand() % 0xFF, // G
				rand() % 0xFF, // B
				rand() % 0xFF  // A
			);
			mlx_put_pixel(image, i, y, color);
		}
	}
}

int32_t main(void)
{
	t_data	data;

	if (!(data.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
		return(1);
	if (!(data.alive = mlx_new_image(data.mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(data.mlx);
		return(1);
	}
	if (mlx_image_to_window(data.mlx, data.alive, 0, 0) == -1)
	{
		mlx_close_window(data.mlx);
		return(1);
	}
	mlx_loop_hook(data.mlx, ft_randomize, data.mlx);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}

