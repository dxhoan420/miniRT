//
// Created by Demeter Xhoan on 2/24/21.
//

#include "../headers/ray_tracing.h"
#include "../headers/miniRT.h"

void		super_ray_tracing(void *mlx, void *window, t_all scene)
{
	int			mlx_x_step;
	int 		mlx_y_step;
	int			view_x_step;
	int 	 	view_y_step;
	float		x_ray;
	float		y_ray;
	t_vector	ray;
	t_viewport	viewport;

	viewport = get_viewport(scene.x_resolution, scene.y_resolution,
						 scene.cameras->field_of_view);
	view_y_step = scene.y_resolution / 2;
	mlx_y_step = 0;
	while (view_y_step >= (-scene.y_resolution / 2))
	{
		y_ray = (float)view_y_step * viewport.y_pixel;//тут можно просто
		// прибавлять
		view_x_step = (-scene.x_resolution / 2);
		mlx_x_step = 0;
		while (view_x_step <= scene.x_resolution / 2)
		{
			x_ray = (float)view_x_step * viewport.x_pixel;
			ray = new_vector(x_ray, y_ray, -1);
			//normalization_of_vector(ray);
			// нахуй нормализация?
			if (distance_to_sphere(*(scene.cameras), ray, *(scene.spheres)) > 0)
				mlx_pixel_put(mlx, window, mlx_x_step, mlx_y_step, scene.spheres->color);
			else
				mlx_pixel_put(mlx, window, mlx_x_step, mlx_y_step, 0);
			view_x_step++;
			mlx_x_step++;
		}
		view_y_step--;
		mlx_y_step++;
	}
}

t_viewport	get_viewport(int x_resolution, int y_resolution, int fov)
{
	t_viewport	viewport;
	float		ratio;

	ratio = (float) x_resolution / (float) y_resolution;
	viewport.width = 2 * tan((float)fov / 2 * (M_PI / 180));
	viewport.height = viewport.width / ratio;
	viewport.x_pixel = viewport.width / (float) x_resolution;
	viewport.y_pixel = viewport.height / (float) y_resolution;
	return (viewport);
}