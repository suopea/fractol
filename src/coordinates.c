/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuopea <ssuopea@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:07:21 by ssuopea           #+#    #+#             */
/*   Updated: 2025/08/22 21:01:09 by ssuopea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	reset_orbits(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->px_count)
	{
		if (data->type == mandelbrot)
		{
			data->orbits[i].r = 0;
			data->orbits[i].i = 0;
		}
		data->escape_times[i] = 0;
		i++;
	}
	data->iteration = 0;
}

void	update_locations(t_data *data)
{
	int	row;
	int	column;
	t_complex	*pixel;

	if (data->type == mandelbrot)
		pixel = data->px;
	else
		pixel = data->orbits;
	row = 0;
	while (row < data->height)
	{
		column = 0;
		while (column < data->width)
		{
			pixel[i(column, row, data)].r = data->location.r + row * data->scale;
			pixel[i(column, row, data)].i = data->location.i + column * data->scale;
			column++;
		}
		row++;
	}
	reset_orbits(data);
}

void	new_location_from_center(t_data *data, int x, int y)
{
	data->location.r += data->px[i(x, y, data)].r - data->px[center(data)].r;
	data->location.i += data->px[i(x, y, data)].i - data->px[center(data)].i;
	update_locations(data);
}

void	zoom_to_point(t_data *data, int x, int y, float change)
{
	if (change < 1)
	{
		data->location.r += (data->px[i(x, y, data)].r - data->location.r) * (1 - change);
		data->location.i += (data->px[i(x, y, data)].i - data->location.i) * (1 - change);
	}
	else
	{
		data->location.r -= (data->px[i(x, y, data)].r - data->location.r) * (change - 1);
		data->location.i -= (data->px[i(x, y, data)].i - data->location.i) * (change - 1);
	}
	data->scale *= change;
	update_locations(data);
	// iterate_until_first_escape(data);
}
