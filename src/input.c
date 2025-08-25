/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuopea <ssuopea@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 20:46:46 by ssuopea           #+#    #+#             */
/*   Updated: 2025/08/22 21:07:44 by ssuopea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "fractal.h"

void	mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods, void *input)
{
	t_data *data = input;
	int	x;
	int y;

	(void)mods;
	clear_screen(data);
	mlx_get_mouse_pos(data->mlx, &x, &y);	
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
		move_center(data, x, y);
}

void	scroll_hook(double xdelta, double ydelta, void *input)
{
	t_data *data = input;
	int x;
	int y;

	(void)xdelta;
	clear_screen(data);
	mlx_get_mouse_pos(data->mlx, &x, &y);	
	if (ydelta > 0)
		zoom_to_point(data, x, y, 1.0 / SCROLL_AMOUNT);
	if (ydelta < 0 && data->scale < 10)
		zoom_to_point(data, x, y, SCROLL_AMOUNT);
}

static void	toggle_pause(t_data *data)
{
	if (data->paused)
		data->paused = false;
	else
		data->paused = true;
}

void	key_hook(mlx_key_data_t keydata, void *input)
{
	t_data	*data;

	data = input;
	if (keydata.key == KEY_ESC && keydata.action == MLX_PRESS)
	{
		free_everything(data);
		mlx_close_window(data->mlx);
	}
	if (keydata.key == KEY_REITERATE && keydata.action == MLX_PRESS)
		reset_orbits(data);
	if (keydata.key == KEY_RESET && keydata.action == MLX_PRESS)
		reset(data);
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
		toggle_pause(data);
}

int	about_to_resize(t_data *data)
{
if (data->resizing)
	{
		if (data->resizing > RESIZE_WAIT)
		{
			data->width = data->new_width;
			data->height = data->new_height;
			data->px_count = data->new_px_count;
			free_everything(data);
			mlx_delete_image(data->mlx, data->frame);
			data->frame = mlx_new_image(data->mlx, data->width, data->height);
			if (!data->frame
				|| mlx_image_to_window(data->mlx, data->frame, 0, 0) < 0)
				free_and_exit(data);
			allocate_everything(data);
			reset(data);
			return (1);
		}
		data->resizing++;
		return (1);
	}
	return (0);
}

void	resize_hook(int32_t width, int32_t height, void *input)
{
	t_data	*data;

	data = input;
	data->new_width = width;
	data->new_height = height;
	data->new_px_count = data->new_width * data->new_height;
	data->resizing = 1;
}
