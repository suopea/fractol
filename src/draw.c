/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuopea <ssuopea@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 20:48:52 by ssuopea           #+#    #+#             */
/*   Updated: 2025/08/23 12:10:42 by ssuopea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	clear_screen(t_data *data)
{
	memset(data->frame->pixels, 0, data->px_count * sizeof(int32_t));
}

static	int32_t	normal(int escape_time, int iterations)
{
	// return (((iterations / escape_time % 16) * 0x111111) << 8 | 0xFF);
	// return ((((iterations - escape_time + 100) % 0xFF) * 0x010101) << 8 | 0xFF);
	return (((((iterations - escape_time + 100) * 20) % 0xFF) * 0x010101) << 8 | 0xFF);
}

void	colorize_pixels(t_data *data)
{
	int	i;
	int	normalized;

	i = 0;
	while (i < data->px_count)
	{
		if (!data->escape_times[i])
			mlx_put_pixel(data->frame, x(i, data), y(i, data), 0xFF);
		else
		{
			normalized = normal(data->escape_times[i], data->iteration);
			mlx_put_pixel(data->frame, x(i, data), y(i, data), normalized);
		}	
		i++;
	}
}
