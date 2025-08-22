
#include "fractal.h"
#include <string.h>

int	main(void)
{
	t_data	data;
	mlx_t	*mlx;

	// mlx = mlx_init(WIDTH, HEIGHT, "hmm", false);
	mlx = mlx_init(WIDTH, HEIGHT, "hmm", false);
	// data.frame = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_image_t *img = mlx_new_image(mlx, WIDTH, HEIGHT);
	memset(img->pixels, 255, WIDTH * HEIGHT * sizeof(int32_t));
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
