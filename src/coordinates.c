/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuopea <ssuopea@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:07:21 by ssuopea           #+#    #+#             */
/*   Updated: 2025/08/22 12:02:05 by ssuopea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	update_locations(t_data *data)
{
	int	row;
	int	column;

	row = 0;
	while (row < HEIGHT)
	{
		column = 0;
		while (column < WIDTH)
		{
			data->points[row * WIDTH + column].origin.i = data->location.i + row * data->scale;
			data->points[row * WIDTH + column].origin.r = data->location.i + column * data->scale;
			column++;
		}
		row++;
	}
}
