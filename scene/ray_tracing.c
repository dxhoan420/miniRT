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

struct s_figure		*get_closer_figure(t_vector camera,t_vector ray,
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

//we need to divide light_ratio for successful result of cross_product
int	put_ambient(int figure_color, int light_color, float light_ratio)
{
	t_vector	orig;
	t_vector	lamp;
	int			r;
	int 		g;
	int 		b;

//	r = figure_color >> 16;
//	g = (figure_color & (0xFF << 8)) >> 8;
//	b = figure_color & 0xFF;

	orig = get_new_vector((float)(figure_color >> 16),
						  (float)((figure_color & (0xFF << 8)) >> 8),
						  (float)(figure_color & 0xFF));
	lamp = get_new_vector((float)(light_color >> 16),
						  (float)((light_color & (0xFF << 8)) >> 8),
						  (float)(light_color & 0xFF));
	light_ratio /= 255;
	lamp = vector_multiplying_by_number(lamp, light_ratio);
	orig = vectors_cross_product(orig, lamp);
//	r = (int)(light_ratio * orig.x);
//	if (r > 255)
//		r = 255;
//	g = (int)(light_ratio * orig.y);
//	if (g > 255)
//		g = 255;
//	b = (int)(light_ratio * orig.z);
//	if (g > 255)
//		g = 255;
//	return (create_rgb(r, g, b));
	return (create_rgb((int)orig.x, (int)orig.y, (int)orig.z));
}

int put_color(t_all scene,t_vector ray)
{
	struct s_figure *figure;

	figure = get_closer_figure(scene.cameras->coordinates, ray, scene.figures);
	if (figure == NULL)
		return (0);
	return (put_ambient(figure->color, scene.ambient_color, scene.ambient_ratio));
	//return (figure->color);
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
