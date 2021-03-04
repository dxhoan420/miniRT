//
// Created by Demeter Xhoan on 2/24/21.
//

#include "../headers/miniRT.h"

t_viewport	get_viewport(int x_resolution, int y_resolution, int fov)
{
	t_viewport	viewport;
	float		ratio;

	ratio = (float) x_resolution / (float) y_resolution;
	viewport.x_size = 2 * tan((float)fov / 2 / 180 * M_PI);
	viewport.y_size = viewport.x_size / ratio;
	viewport.x_pixel = viewport.x_size / (float) x_resolution;
	viewport.y_pixel = viewport.y_size / (float) y_resolution;
	return (viewport);
}

struct s_figure		*get_closer_figure(struct s_camera camera,t_vector ray,
										  t_figures *figures)
{
	struct s_figure *closer_one = NULL;
	float 			minimum_positive = 3.402823466e38f;
	float			result;

	while (figures != NULL)
	{
		if (figures->id == SPHERE)
			result = distance_to_sphere(camera, ray, *figures);
		if (result > 0 && result < minimum_positive)
		{
			minimum_positive = result;
			closer_one = figures;
		}
		figures = figures->next;
	}
	return(closer_one);
}

int put_color(struct s_camera camera,t_vector ray, t_figures *figures)
{
	struct s_figure *figure;

	figure = get_closer_figure(camera, ray, figures);
	if (figure == NULL)
		return (0);
	return (figure->color);
}

void		super_ray_tracing(void *mlx, void *window, t_all scene)
{
	int			mlx_x_step;
	int 		mlx_y_step;
	float		x_ray;
	float		y_ray;
	t_vector	ray;
	t_viewport	viewport;

	viewport = get_viewport(scene.x_resolution, scene.y_resolution,
						 scene.cameras->field_of_view);
	y_ray = (float)scene.y_resolution / 2 * viewport.y_pixel;
	mlx_y_step = 0;
	while (mlx_y_step < scene.y_resolution)
	{
		y_ray -= viewport.y_pixel;
		x_ray = (-(float)scene.x_resolution / 2) * viewport.x_pixel;
		mlx_x_step = 0;
		while (mlx_x_step < scene.x_resolution)
		{
			ray = get_new_vector(x_ray, y_ray, -1);
			//printf("%f\t%f\t%f\n", ray.x, ray.y, ray.z);
			mlx_pixel_put(mlx, window, mlx_x_step, mlx_y_step,
				 put_color(*(scene.cameras), ray, scene.figures));
			x_ray += viewport.x_pixel;
			mlx_x_step++;
		}
		printf("\n");
		mlx_y_step++;
	}
}

//if (distance_to_sphere(*(scene.cameras), ray, *(scene.spheres)) > 0)
//				mlx_pixel_put(mlx, window, mlx_x_step, mlx_y_step, scene.spheres->color);
//			else
//				mlx_pixel_put(mlx, window, mlx_x_step, mlx_y_step, 0);


//void		new_ray_tracing(void *mlx, void *window, t_all scene)
//{
//	int			x_res_counter;
//	float 		x_pixel_count;
//	t_vector	ray;
//	t_viewport	viewport;
//
//	viewport = get_viewport(scene.x_resolution, scene.y_resolution,
//							scene.cameras->field_of_view);	//переделать под
//							// все камеры!!!
//	while (scene.y_resolution > 0)
//	{
//		x_res_counter = scene.x_resolution;
//		x_pixel_count = viewport.x_size;
//		while (x_res_counter > 0)
//		{
//			ray = get_new_vector(x_pixel_count, viewport.y_size, -1);
//			printf("%f\t%f\t%f\n", ray.x, ray.y, ray.z);
//			if (distance_to_sphere(*(scene.cameras), ray, *(scene.spheres)) > 0)
//				mlx_pixel_put(mlx, window, x_res_counter,
//				  scene.y_resolution,  scene.spheres->color);
//			else
//				mlx_pixel_put(mlx, window, x_res_counter,
//				  scene.y_resolution, 0);
//			x_res_counter--;
//			x_pixel_count -= viewport.x_pixel;
//		}
//		printf("\n");
//		viewport.y_size -= viewport.y_pixel;
//		scene.y_resolution--;
//	}
//}

