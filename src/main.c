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

#include "fractal.h"

static void	loop_hook(void *input);

int main(void)
{
	t_data	data;

	if (!initialize(&data))
		return (1);
	if (!initialize_mlx(&data))
	{
		mlx_terminate(data.mlx);
		return (1);
	}
	mlx_mouse_hook(data.mlx, &mouse_hook, &data);
	mlx_scroll_hook(data.mlx, &scroll_hook, &data);
	mlx_loop_hook(data.mlx, &loop_hook, &data);
	mlx_key_hook(data.mlx, &key_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}

static void	loop_hook(void *input)
{
	t_data	*data;
	int		i;

	data = input;
	i = 0;
	while (i < data->work_per_frame)
	{
		iterate_all_pixels_once(data);
		i++;
	}
	colorize_pixels(data);
}
