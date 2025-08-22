/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuopea <ssuopea@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:06:27 by ssuopea           #+#    #+#             */
/*   Updated: 2025/08/22 17:20:07 by ssuopea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int	initialize(t_data *data)
{
	data->px = malloc(WIDTH * HEIGHT * sizeof(t_complex));
	if (!data->px)
		return (0);
	data->orbits = malloc(WIDTH * HEIGHT * sizeof(t_complex));
	if (!data->orbits)
	{
		free(data->px);
		return (0);
	}
	data->scale = DEFAULT_SCALE;
	data->location.i = 0;
	data->location.r = 0;
	update_origins(data);
	move_center(data, 0, 0);
	data->iteration = 0;
	data->work_per_frame = DEFAULT_WORK_PER_FRAME;
	return (1);
}
