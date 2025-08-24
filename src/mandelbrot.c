/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuopea <ssuopea@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 11:20:50 by ssuopea           #+#    #+#             */
/*   Updated: 2025/08/23 13:23:08 by ssuopea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

static void	iterate_pixel(double *ci, double *cr, double *zi, double *zr)
{
	double zr2 = *zr * *zr;
	double zi2 = *zi * *zi;
	*zi = (*zr + *zr) * *zi + *ci;
	*zr = zr2 - zi2 + *cr;
}

static int	escaped(t_complex orbit)
{
	return (hypot(orbit.i, orbit.r) > 4);
}

// static double	smoothing(t_complex z)
// {
// 	double	log_z = log(z.i * z.i + z.r * z.r) / 2;
// 	return (log(log_z / M_LN2) / M_LN2);
// }

void	iterate_all_pixels_once(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->px_count)
	{
		if (1)	
		{
			iterate_pixel(&data->px[i].r, &data->px[i].i, &data->orbits[i].r, &data->orbits[i].i);
			if (escaped(data->orbits[i]))
			{
				data->escape_times[i] = rint(data->iteration);
				// data->escape_times[i] -= smoothing(data->orbits[i]);
			}
		}
		i++;
	}
	data->iteration++;
}
