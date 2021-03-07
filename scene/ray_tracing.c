//
// Created by Demeter Xhoan on 2/24/21.
//

#include "../headers/miniRT.h"

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

float		get_closer_figure_distance(t_vector camera, t_vector ray,
										t_figures *figures, struct s_figure **result)
{
	struct s_figure *closer_one = NULL;
	float 			minimum_positive = 3.402823466e38f;
	float			distance;

	while (figures != NULL)
	{
		if (figures->id == SPHERE)
			distance = distance_to_sphere(camera, ray, *figures);
		if (distance > 0 && distance < minimum_positive)
		{
			minimum_positive = distance;
			closer_one = figures;
		}
		figures = figures->next;
	}
	*result = closer_one;
	return(minimum_positive);
}

int	create_color(t_rgb orig, t_rgb light)
{
	orig.r *= light.r;
	orig.g *= light.g;
	orig.b *= light.b;
	return ((int)orig.r << 16 | (int)orig.g << 8 | (int)orig.b);
}

int put_color(t_all scene,t_vector ray)
{
	struct s_figure *figure;
	t_rgb			result;
	float			lights_quantity;
	struct s_light	*light;
	float			distance;

	distance = get_closer_figure_distance(scene.cameras->coordinates, ray,
										  scene.figures, &figure);
	if (figure == NULL)
		return (0);
	result = scene.ambient_rgb_norm;
	lights_quantity = 1;
	light = scene.lights;
	while (light != NULL)
	{
		lights_quantity++;
		if (1)//добавить условие на тень
		{
			t_vector vector_distance = vector_multiplication_by_number(ray,
															  distance);
			t_vector crossing = vectors_addition(scene.cameras->coordinates,
										vector_distance);
			t_vector norm = vector_normalization(vectors_subtraction
					(crossing, figure->first_or_center));
			float ratio = vectors_dot_product(norm, light->coordinates) /
					(vector_length(norm) * vector_length(light->coordinates));
			result = rgbs_addition(result,
								   rgb_multiplication(light->rgb_norm, ratio));
			//пиздец как теперь всё это спрятать нахуй.....
		}
		light = light->next;
	}
	return (create_color(figure->rgb, rgb_division(result, lights_quantity)));
}

void		super_ray_tracing(void *mlx, void *window, t_all scene)
{
	int			mlx_x;
	int 		mlx_y;
	t_vector	ray;
	t_viewport	viewport;

	viewport = get_viewport(scene.x_resolution, scene.y_resolution,
						 scene.cameras->field_of_view);
	ray.z = -1;//вот эту хуйню поменять надо!
	ray.y = (float)scene.y_resolution / 2 * viewport.y_pixel;
	mlx_y = 0;
	while (mlx_y < scene.y_resolution)
	{
		ray.x = (-(float)scene.x_resolution / 2) * viewport.x_pixel;
		mlx_x = 0;
		while (mlx_x < scene.x_resolution)
		{
			mlx_pixel_put(mlx, window, mlx_x, mlx_y, put_color(scene, ray));
			ray.x += viewport.x_pixel;
			mlx_x++;
		}
		ray.y -= viewport.y_pixel;
		mlx_y++;
	}
}
