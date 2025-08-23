/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuopea <ssuopea@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 20:46:46 by ssuopea           #+#    #+#             */
/*   Updated: 2025/08/22 21:07:44 by ssuopea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods, void *input)
{
	t_data *data = input;
	int	x;
	int y;

	(void)mods;
	clear_screen(data);
	mlx_get_mouse_pos(data->mlx, &x, &y);	
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
		move_center(data, x, y);
}

void	scroll_hook(double xdelta, double ydelta, void *input)
{
	t_data *data = input;
	int x;
	int y;

	(void)xdelta;
	clear_screen(data);
	mlx_get_mouse_pos(data->mlx, &x, &y);	
	if (ydelta > 0)
		zoom_to_point(data, x, y, 1.0 / SCROLL_AMOUNT);
	if (ydelta < 0 && data->scale < 10)
		zoom_to_point(data, x, y, SCROLL_AMOUNT);
}

