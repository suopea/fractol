/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuopea <ssuopea@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 12:47:25 by ssuopea           #+#    #+#             */
/*   Updated: 2025/08/22 14:24:14 by ssuopea          ###   ########.fr       */
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

typedef struct s_data
{
	t_complex*		px;
	t_complex*		orbits;
	mlx_image_t*	rendered;
	double			scale;
	int				iteration;
	t_complex		location;
	int				work_per_frame;			
	mlx_t*			mlx;
}	t_data;

void	update_origins(t_data *data);
void	move_center(t_data *data, int x, int y);
int		i(int x, int y);
int		center(void);
void	zoom_to_point(t_data *data, int x, int y, float change);

#endif
