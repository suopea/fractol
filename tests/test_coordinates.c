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
					data.points[row * WIDTH + column].origin.r,
					data.points[row * WIDTH + column].origin.i);
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
	update_locations(data);
	print_points(*data);

	printf("\n\n");
}

int	main(void)
{
	t_data	data;

	data.points = malloc(WIDTH * HEIGHT * sizeof(t_points));
	test(&data, 1, 0, 0);
	test(&data, 2, 0, 0);
	test(&data, 2, -1, -1);
	test(&data, 0.5, -1, -1);

}

