
#include "fractal.h"
#include <stdio.h>

int	near(int n, t_complex px)
{
	if (!n)
	{
		if ((-1 < px.i && px.i < 1) || (-1 < px.r && px.r < 1))
			return (1);
		else
			return (0);
	}
	int	i_int = lrint(px.i);
	int	r_int = lrint(px.r);
	if (i_int % n == 0 || r_int % n == 0)
		return (1);
	return (0);
}

void	draw_grid(t_data *data)
{
	int	row;
	int col;

	row = 0;
	while (row < HEIGHT)
	{
		col = 0;
		while (col < WIDTH)
		{
			if (near(10, data->px[i(col, row)]))
				mlx_put_pixel(data->frame, col, row, 0xFF0000FF);
			if (near(100, data->px[i(col, row)]))
				mlx_put_pixel(data->frame, col, row, 0xFFFF00FF);
			if (near(0, data->px[i(col, row)]))
				mlx_put_pixel(data->frame, col, row, 0xFFFFFFFF);
			col++;
		}
		row++;
	}
}

void	loop_hook(void *data)
{
	data = (t_data *)data;

	draw_grid(data);
}

int	main(void)
{
	t_data	data;

	initialize(&data);
	initialize_mlx(&data);
	mlx_loop_hook(data.mlx, loop_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}
