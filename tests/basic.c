
#include "fractal.h"
#include <string.h>

int	main(void)
{
	// t_data	data;
	mlx_t	*mlx;

	// mlx = mlx_init(500, 500, "hmm", false);
	mlx = mlx_init(500, 500, "hmm", false);
	// data.frame = mlx_new_image(mlx, 500, 500);
	mlx_image_t *img = mlx_new_image(mlx, 500, 500);
	memset(img->pixels, 255, 500 * 500 * sizeof(int32_t));
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
