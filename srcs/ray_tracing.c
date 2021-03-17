//
// Created by Demeter Xhoan on 2/24/21.
//

#include "../hdrs/miniRT.h"

typedef struct s_viewport
{
	float	x_size;
	float	y_size;
	float	x_pixel;
	float	y_pixel;
}			t_viewport;

t_viewport	get_viewport(int x_resolution, int y_resolution, int fov)
{
	t_viewport	viewport;
	float		ratio;

	ratio = (float) x_resolution / (float) y_resolution;
	viewport.x_size = (float)(2 * tan((float)fov / 2 / 180 * M_PI));
	viewport.y_size = viewport.x_size / ratio;
	viewport.x_pixel = viewport.x_size / (float) x_resolution;
	viewport.y_pixel = viewport.y_size / (float) y_resolution;
	return (viewport);
}

void	render_scene(void *mlx, void *window, t_all scene)
{
	int			mlx_x;
	int			mlx_y;
	t_vec		ray;
	t_viewport	viewport;

	viewport = get_viewport(scene.x_resolution, scene.y_resolution,
			 scene.camera.field_of_view);
	ray.z = 1;
	ray.y = (float)scene.y_resolution / 2 * viewport.y_pixel;
	mlx_y = 0;
	while (mlx_y < scene.y_resolution)
	{
		ray.x = (-(float)scene.x_resolution / 2) * viewport.x_pixel;
		mlx_x = 0;
		while (mlx_x < scene.x_resolution)
		{
			mlx_pixel_put(mlx, window, mlx_x, mlx_y, get_pixel_color(scene,
				create_ray(scene.camera.coordinates, vector_norm(ray))));
			ray.x += viewport.x_pixel;
			mlx_x++;
		}
		ray.y -= viewport.y_pixel;
		mlx_y++;
	}
}
