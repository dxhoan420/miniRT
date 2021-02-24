//
// Created by Demeter Xhoan on 2/24/21.
//

#include "../headers/ray_tracing.h"
#include "../headers/miniRT.h"

void		super_ray_tracing(void *mlx, void *window, t_all scene)
{
	int			mlx_x;
	int 		mlx_y = 0;
	int			x_angle;
	int 		y_angle;
	float		x_ray;
	float		y_ray;
	t_vector	ray;
	t_viewport	viewport;

	viewport = get_viewport(scene);
	y_angle = scene.y_resolution / 2;
	while (y_angle > (-scene.y_resolution / 2))
	{
		y_ray = (float)y_angle * viewport.y_pixel;
		x_angle = (-scene.x_resolution / 2);
		mlx_x = 0;
		while (x_angle < scene.x_resolution / 2)
		{
			x_ray = (float)x_angle * viewport.x_pixel;
			ray = new_vector(x_ray, y_ray, -1);
			//нахуй нормализация?
			if (distance_to_sphere(*(scene.cameras), ray, *(scene.spheres)) > 0)
				mlx_pixel_put(mlx, window, mlx_x, mlx_y, scene.spheres->color);
			else
				mlx_pixel_put(mlx, window, mlx_x, mlx_y, 0);
			x_angle++;
			mlx_x++;
		}
		y_angle--;
		mlx_y++;
	}
}

t_viewport	get_viewport(t_all scene)
{
	t_viewport	viewport;
	float		ratio;

	ratio = scene.x_resolution / scene.y_resolution;
	viewport.width = 1;
	viewport.height = viewport.width / ratio;
	viewport.x_pixel = viewport.width / scene.x_resolution;
	viewport.y_pixel = viewport.height / scene.y_resolution;
	return (viewport);
}