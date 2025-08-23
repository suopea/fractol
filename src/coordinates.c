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

void	update_origins(t_data *data)
{
	int	row;
	int	column;

	row = 0;
	while (row < HEIGHT)
	{
		column = 0;
		while (column < WIDTH)
		{
			data->px[i(column, row)].r = data->location.r + row * data->scale;
			data->px[i(column, row)].i = data->location.i + column * data->scale;
			column++;
		}
		row++;
	}
}

void	move_center(t_data *data, int x, int y)
{
	data->location.r += data->px[i(x, y)].r - data->px[center()].r;
	data->location.i += data->px[i(x, y)].i - data->px[center()].i;
	update_origins(data);
}

void	zoom_to_point(t_data *data, int x, int y, float change)
{
	if (change < 1)
	{
		data->location.r += (data->px[i(x, y)].r - data->location.r) * (1 - change);
		data->location.i += (data->px[i(x, y)].i - data->location.i) * (1 - change);
	}
	else
	{
		data->location.r -= (data->px[i(x, y)].r - data->location.r) * (change - 1);
		data->location.i -= (data->px[i(x, y)].i - data->location.i) * (change - 1);
	}
	data->scale *= change;
	update_origins(data);
}
