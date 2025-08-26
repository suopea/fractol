/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuopea <ssuopea@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 20:46:46 by ssuopea           #+#    #+#             */
/*   Updated: 2025/08/26 14:55:21 by ssuopea          ###   ########.fr       */
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
		new_location_from_center(data, x, y);
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
	{
		data->zoom_count++;
		data->waiting_to_zoom++;
	}
	if (ydelta < 0 && data->scale < 10)
		apply_zoom(data, x, y, SCROLL_AMOUNT);
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
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		data->wait_to_draw += SPEED_CHANGE;
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		if (data->wait_to_draw - SPEED_CHANGE > 0)
			data->wait_to_draw -= SPEED_CHANGE;
}

static void	reset_but_preserve_location(t_data *data)
{
	t_complex	location_temp;
	double		scale_temp;	

	location_temp = data->location;
	scale_temp = data->scale * ((float)data->width / data->new_width);
	data->width = data->new_width;
	data->height = data->new_height;
	data->px_count = data->new_px_count;
	mlx_delete_image(data->mlx, data->frame);
	data->frame = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->frame
		|| mlx_image_to_window(data->mlx, data->frame, 0, 0) < 0)
		free_and_exit(data);
	free_everything(data);
	allocate_everything(data);
	reset(data);
	data->location = location_temp;
	data->scale = scale_temp;
	update_origins(data);	
}

int	about_to_resize(t_data *data)
{
	if (data->waiting_to_resize)
	{
		if (data->waiting_to_resize > RESIZE_WAIT)
		{
			reset_but_preserve_location(data);
			return (1);
		}
		data->waiting_to_resize++;
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
	data->waiting_to_resize = 1;
}
