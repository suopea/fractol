/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuopea <ssuopea@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 20:48:52 by ssuopea           #+#    #+#             */
/*   Updated: 2025/08/22 20:50:58 by ssuopea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	clear_screen(t_data *data)
{
	memset(data->frame->pixels, 0, WIDTH * HEIGHT * sizeof(int32_t));
}

