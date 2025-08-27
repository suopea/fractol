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
		new_location_from_center(data, x, y);
}

void	scroll_hook(double xdelta, double ydelta, void *input)
{
	t_data *data = input;

	(void)xdelta;
	printf("%.2f\n", ydelta);
	if (ydelta > 0)
	{
		data->waiting_to_zoom = 1;	
		data->to_zoom_soon *= 1.0 / (SCROLL_AMOUNT + (ydelta / 10));
	}
	if (ydelta < 0 && data->scale < DEFAULT_SCALE)
	{
		data->to_zoom_soon *= (SCROLL_AMOUNT - (ydelta / 50));
		if (data->waiting_to_zoom == 0)
		{
			get_cursor_location_and_zoom(data, data->to_zoom_soon);
			data->to_zoom_soon = 1;
		}
		else
		{
			data->waiting_to_zoom = ZOOM_WAIT;	
		}
	}
}

static void	toggle_pause(t_data *data)
{
	if (data->paused)
		data->paused = false;
	else
		data->paused = true;
}

static void	toggle_cursor(t_data *data)
{
	if (data->cursor_visible)
	{
		mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);	
		data->cursor_visible = false;
	}
	else
	{
		mlx_set_cursor_mode(data->mlx, MLX_MOUSE_NORMAL);	
		data->cursor_visible = true;
	}
}

void	key_hook(mlx_key_data_t keydata, void *input)
{
	t_data	*data;

	data = input;
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == KEY_ESC)
	{
		free_everything(data);
		mlx_close_window(data->mlx);
	}
	if (keydata.key == KEY_REITERATE)
		reset_orbits(data);
	if (keydata.key == KEY_RESET)
		reset(data);
	if (keydata.key == MLX_KEY_SPACE)
		toggle_pause(data);
	if (keydata.key == MLX_KEY_LEFT)
		data->wait += SPEED_CHANGE;
	if (keydata.key == MLX_KEY_RIGHT)
		if (data->wait - SPEED_CHANGE > 0)
			data->wait -= SPEED_CHANGE;
	if (keydata.key == MLX_KEY_Z)
		get_cursor_location_and_zoom(data, MEGAZOOM);
	if (keydata.key == MLX_KEY_C)
		toggle_cursor(data);
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
	update_locations(data);	
}

int	about_to_resize(t_data *data)
{
	if (data->resizing)
	{
		if (data->resizing > RESIZE_WAIT)
		{
			reset_but_preserve_location(data);
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
