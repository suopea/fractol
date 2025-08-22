#include "fractal.h"
#include <stdio.h>

void	print_points(t_data data)
{
	int		row = 0;
	int		column;

	while (row < HEIGHT)
	{
		column = 0;
		while (column < WIDTH)
		{
			printf("%.1f, %.1f\t", 
					data.px[i(column, row)].r,
					data.px[i(column, row)].i);
			column++;
		}
		printf("\n");
		row++;
	}
}

void	test(t_data *data, double s, double i, double r)
{

	printf("testing scale %.1f, location %.1f, %.1f\n\n", s, i, r);

	data->scale = s;
	data->location.i = i;
	data->location.r = r;
	update_origins(data);
	print_points(*data);

	printf("\n\n");
}

void	test_move(t_data *data, int x, int y)
{
	printf("making (%i, %i) the new center\n\n", x, y);
	move_center(data, x, y);
	print_points(*data);
	printf("\n\n");
}

void	test_zoom(t_data *data, int x, int y, float change)
{
	printf("scaling %.1f at (%i, %i)\n\n", change, x, y);
	
	zoom_to_point(data, x, y, change);
	print_points(*data);

	printf("\n\n");
}

int	main(void)
{
	t_data	data;

	data.px = malloc(WIDTH * HEIGHT * sizeof(t_complex));
	test(&data, 1, 0, 0);
	test(&data, 2, 0, 0);
	test(&data, 2, -1, -1);
	test(&data, 0.5, -1, -1);

	test_move(&data, 1, 1);
	test_move(&data, 3, 1);

	test(&data, 1, 0, 0);

	test_zoom(&data, 1, 1, 2);
	test_zoom(&data, 3, 1, 0.5);
	test_zoom(&data, 3, 1, 1);

}

