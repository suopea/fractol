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

static void	loop_hook(void *input);

int main(void)
{
	t_data	data;

	// mlx_set_setting(MLX_STRETCH_IMAGE, true);	
	if (!initialize_program(&data))
		return (1);
	if (!initialize_mlx(&data))
	{
		mlx_terminate(data.mlx);
		return (1);
	}
	mlx_mouse_hook(data.mlx, &mouse_hook, &data);
	mlx_scroll_hook(data.mlx, &scroll_hook, &data);
	mlx_resize_hook(data.mlx, &resize_hook, &data);
	mlx_loop_hook(data.mlx, &loop_hook, &data);
	mlx_key_hook(data.mlx, &key_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
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
	while (data->all_black)
		iterate_until_first_escape(data);
	i = 0;
	while (i < data->work_per_frame)
	{
		iterate_all_pixels_once(data);
		i++;
	}
	colorize_pixels(data);
	usleep(data->wait);
}
