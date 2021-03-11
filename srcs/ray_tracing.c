//
// Created by Demeter Xhoan on 2/24/21.
//

#include "../hdrs/miniRT.h"

t_viewport		get_viewport(int x_resolution, int y_resolution, int fov)
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

struct s_figure	*get_closer_figure(t_ray ray, t_figures *figures)
{
	struct s_figure *closer_one = NULL;
	float 			minimum_positive = MAXFLOAT;
	float			distance;

	while (figures != NULL)
	{
		if (figures->id == SPHERE)
			distance = distance_to_sphere(ray, *figures);
		if (distance > FLT_EPSILON && distance < minimum_positive)
		{
			minimum_positive = distance;
			closer_one = figures;
		}
		figures = figures->next;
	}
	if (closer_one != NULL)
		closer_one->distance = minimum_positive;
	return(closer_one);
}

t_rgb			count_sphere_color(struct s_figure figure, struct s_light light,
		t_rgb color, struct	s_ray ray)
{
	t_vector vector_distance;
	t_vector crossing;
	t_vector norm;
	float ratio;

	vector_distance = vector_multiply_by_number(ray.dir, figure.distance);
	crossing = vectors_addition(ray.src, vector_distance);
	norm = vector_norm(vectors_subtraction(crossing, figure.first_or_center));
	ratio = vectors_dot_product(norm, light.coordinates) /
		(vector_length(norm) * vector_length(light.coordinates));
	t_vector R = vectors_subtraction(vector_multiply_by_number(norm,
							2 * vectors_dot_product(norm, light.coordinates))
									, light.coordinates);
	float r_dot_v = vectors_dot_product(R, vector_multiply_by_number(ray
	.dir, -1));
	if (ratio > 0)
	{
		if (r_dot_v > 0)
			ratio += pow(r_dot_v / (vector_length(R) * vector_length
					(vector_multiply_by_number(ray .dir, -1))), SHININESS);
		return (rgbs_addition(color, rgb_multiply(light.rgb_norm, ratio)));
	}
	else
		return (color);
}

//int				is_shaded()
//{
//
//}

int				put_color(t_all scene, t_ray ray)
{
	struct s_figure *figure;
	t_rgb			result;
	//float			lights_quantity;

	figure = get_closer_figure(ray, scene.figures);
	if (figure == NULL)
		return (0);
	result = scene.ambient_rgb_norm;
	//lights_quantity = 1;
	while (scene.lights != NULL)
	{
		//lights_quantity++;
		if (1)//добавить условие на тень
			result = count_sphere_color(*figure, *(scene.lights), result, ray);
		scene.lights = scene.lights->next;
	}
	//return (create_color(figure->rgb, rgb_division(result, lights_quantity)));
	return (create_color(figure->rgb, result));

}

void			super_ray_tracing(void *mlx, void *window, t_all scene)
{
	int			mlx_x;
	int 		mlx_y;
	t_ray 		ray;
	t_viewport	viewport;

	viewport = get_viewport(scene.x_resolution, scene.y_resolution,
						 scene.cameras->field_of_view);
	ray.src = scene.cameras->coordinates;
	ray.dir.z = -1;//вот эту хуйню поменять надо!
	ray.dir.y = (float)scene.y_resolution / 2 * viewport.y_pixel;
	mlx_y = 0;
	while (mlx_y < scene.y_resolution)
	{
		ray.dir.x = (-(float)scene.x_resolution / 2) * viewport.x_pixel;
		mlx_x = 0;
		while (mlx_x < scene.x_resolution)
		{
			mlx_pixel_put(mlx, window, mlx_x, mlx_y, put_color(scene, ray));
			ray.dir.x += viewport.x_pixel;
			mlx_x++;
		}
		ray.dir.y -= viewport.y_pixel;
		mlx_y++;
	}
}
