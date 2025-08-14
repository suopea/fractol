/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuopea <ssuopea@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 12:47:25 by ssuopea           #+#    #+#             */
/*   Updated: 2025/08/14 17:03:30 by ssuopea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_H
# define FRACTAL_H
# include <math.h>
# include "MLX42/MLX42.h"
# define WIDTH 512
# define HEIGHT 512

typedef struct s_pixels
{
	double	origin_r;
	double	origin_i;
	double	orbit_r;
	double	orbit_i;
	double	nearest_orbit_r;
	double	nearest_orbit_i;
}	t_pixels;

typedef struct s_data
{
	t_pixels*		new;
	mlx_image_t*	alive;
	mlx_image_t*	ghost;
	double			scale;
	int				iteration;
	double			view_r;
	double			view_i;
	int				work_per_frame;			
	mlx_t*			mlx;
}	t_data;

#endif
