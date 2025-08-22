/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuopea <ssuopea@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 12:47:25 by ssuopea           #+#    #+#             */
/*   Updated: 2025/08/22 11:42:17 by ssuopea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_H
# define FRACTAL_H
# include <math.h>
# include <stdint.h>
# include <stdbool.h>
# include <stdlib.h>
# include "MLX42/MLX42.h"
# define WIDTH 5
# define HEIGHT 5

typedef struct s_complex
{
	double	r;
	double	i;
}	t_complex;

typedef struct s_points
{
	t_complex	origin;
	t_complex	orbit;
	t_complex	nearest;
}	t_points;

typedef struct s_data
{
	t_points*		points;
	mlx_image_t*	live_frame;
	mlx_image_t*	ghost_frame;
	double			scale;
	int				iteration;
	t_complex		location;
	int				work_per_frame;			
	mlx_t*			mlx;
}	t_data;

void	update_locations(t_data *data);

#endif
