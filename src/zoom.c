/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuopea <ssuopea@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 10:48:44 by ssuopea           #+#    #+#             */
/*   Updated: 2025/08/27 10:55:37 by ssuopea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

static int32_t	get_pixel_color(uint8_t *pixels, int i)
{
	pixels += i * 4;
	return ((pixels[0] << 24) + (pixels[1] << 16) + (pixels[2] << 8) + pixels[3]);
}

static void		rotate_pixel(t_data *data, int x, int y)
{
	uint32_t	color;

	if (0 > x || x > data->width || 0 > y || y > data->height)
		return ;
	color = get_pixel_color(data->frame->pixels, i(x, y, data));
	color = (color + 0x88888800) % 0xFFFFFFFF;
	mlx_put_pixel(data->frame, x, y, color);
}

void	draw_zoom_box(t_data *data)
{
	int32_t	mouse_x;
	int32_t	mouse_y;
	int		i;

	mlx_get_mouse_pos(data->mlx, &mouse_x, &mouse_y);
	i = 0;
	while (i < data->height)
	{
		rotate_pixel(data, mouse_x - data->width * data->to_zoom_soon / 2, i);	
		rotate_pixel(data, mouse_x + data->width * data->to_zoom_soon / 2, i);	
		i++;
	}
	i = 0;
	while (i < data->width)
	{
		rotate_pixel(data, i, mouse_y - data->height * data->to_zoom_soon / 2);	
		rotate_pixel(data, i, mouse_y + data->height * data->to_zoom_soon / 2);	
		i++;
	}
}
