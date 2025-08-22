
#include "MLX42/MLX42.h"
#include "fractal.h"
#include <stdio.h>

void	print_cursor_coordinates(t_data *data)
{
	int32_t x;
	int32_t y;
	char	*string;

	string = malloc(1000);
	mlx_get_mouse_pos(data->mlx, &x, &y);	
	sprintf(string, "px: %i, %i | plane: %.1f, %.1f", x, y, data->px[i(x, y)].r, data->px[i(x, y)].i);
	mlx_set_window_title(data->mlx, string);
	free(string);
}

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

	draw_grid(data);
	print_cursor_coordinates(data);
}

int	main(void)
{
	t_data	data;

	initialize(&data);
	initialize_mlx(&data);
	draw_grid(&data);

	mlx_mouse_hook(data.mlx, &mouse_hook, &data);
	mlx_scroll_hook(data.mlx, &scroll_hook, &data);
	mlx_loop_hook(data.mlx, loop_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}
