/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuopea <ssuopea@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:20:59 by ssuopea           #+#    #+#             */
/*   Updated: 2025/08/26 14:58:57 by ssuopea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "fractal.h"

static t_complex	location_from_zoom(t_data *data, int x, int y, float change)
{
	t_complex	out;

	if (change < 1)
	{
		out.r += (data->px[i(x, y, data)].r - data->location.r) * (1 - change);
		out.i += (data->px[i(x, y, data)].i - data->location.i) * (1 - change);
	}
	else
	{
		out.r -= (data->px[i(x, y, data)].r - data->location.r) * (change - 1);
		out.i -= (data->px[i(x, y, data)].i - data->location.i) * (change - 1);
	}
	return (out);
}

void	apply_zoom(t_data *data, int x, int y, float change)
{
	data->location = location_from_zoom(data, x, y, change);	
	data->scale *= change;
	update_origins(data);
}

void	are_we_zooming(t_data *data)
{
	int	x;
	int	y;

	if (data->waiting_to_zoom)
	{
		if (data->waiting_to_zoom > ZOOM_WAIT)
		{
			mlx_get_mouse_pos(data->mlx, &x, &y);
			printf("waiting %i, count %i\n", data->waiting_to_zoom, data->zoom_count);
			apply_zoom(data, x, y, 1.0 / (data->zoom_count * SCROLL_AMOUNT));
			data->waiting_to_zoom = 0;
			data->zoom_count = 0;
			return ;
		}
	data->waiting_to_zoom++;
	}
}
