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

static void	iterate_pixel(t_complex *c, t_complex *z, t_data *data, int i)
{
	double	i_squared;
	double	r_squared;

	i_squared = z->i * z->i;
	r_squared = z->r * z->r;
	z->r = (z->i + z->i) * z->r + c->r;
	z->i = i_squared - r_squared + c->i;
	if (i_squared + r_squared > 4)
		data->escape_times[i] = data->iteration;
}

static void	iterate_and_check_escape(t_complex *c, t_complex *z, t_data *data, int i)
{
	double	i_squared;
	double	r_squared;

	i_squared = z->i * z->i;
	r_squared = z->r * z->r;
	z->r = (z->i + z->i) * z->r + c->r;
	z->i = i_squared - r_squared + c->i;
	if (i_squared + r_squared > 4)
	{
		data->escape_times[i] = data->iteration;
		data->all_black = 0;
	}
}

void	iterate_julia_once(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->px_count)
	{
		if (!data->escape_times[i])	
			iterate_pixel(&data->c, &data->orbits[i], data, i);
		i++;
	}
	data->iteration++;
}

void	iterate_mandelbrot_once(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->px_count)
	{
		if (!data->escape_times[i])	
			iterate_pixel(&data->px[i], &data->orbits[i], data, i);
		i++;
	}
	data->iteration++;
}

void	iterate_until_first_escape(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->px_count)
	{
		iterate_and_check_escape(&data->px[i], &data->orbits[i], data, i);
		i++;
	}
	data->iteration++;
}
