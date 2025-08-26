/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuopea <ssuopea@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:07:21 by ssuopea           #+#    #+#             */
/*   Updated: 2025/08/26 14:48:52 by ssuopea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	reset_orbits(t_data *data)
{
	int	i;

	i = 0;
	data->iteration = 0;
	while (i < data->px_count)
	{
		data->orbits[i].r = 0;
		data->orbits[i].i = 0;
		data->escape_times[i] = 0;
		i++;
	}
}

void	update_origins(t_data *data)
{
	int	row;
	int	column;

	row = 0;
	while (row < data->height)
	{
		column = 0;
		while (column < data->width)
		{
			data->px[i(column, row, data)].r = data->location.r + row * data->scale;
			data->px[i(column, row, data)].i = data->location.i + column * data->scale;
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
	update_origins(data);
}

