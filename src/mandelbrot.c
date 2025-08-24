/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuopea <ssuopea@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 11:20:50 by ssuopea           #+#    #+#             */
/*   Updated: 2025/08/24 10:29:19 by ssuopea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

static void	iterate_pixel(t_complex *c, t_complex *z)
{
	double temp = z->i * z->i - z->r * z->r;
	z->r = (z->i + z->i) * z->r + c->r;
	z->i = temp + c->i;
}

static int	escaped(t_complex orbit)
{
	return (hypot(orbit.i, orbit.r) > 4);
}

void	iterate_all_pixels_once(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->px_count)
	{
		iterate_pixel(&data->px[i], &data->orbits[i]);
		if (escaped(data->orbits[i]))
			data->escape_times[i] = data->iteration;
		i++;
	}
	data->iteration++;
}
