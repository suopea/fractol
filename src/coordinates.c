/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuopea <ssuopea@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:07:21 by ssuopea           #+#    #+#             */
/*   Updated: 2025/08/22 14:24:45 by ssuopea          ###   ########.fr       */
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
