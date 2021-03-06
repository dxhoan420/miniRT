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

	figure = get_closer_figure(scene.cameras->coordinates, ray, scene.figures);
	if (figure == NULL)
		return (0);
	result = rgb_multiplying(scene.ambient_rgb_norm, 1);//добавить
	// умножение на интенсивность от нормали
	lights_quantity = 1;
	light = scene.lights;
	while (light != NULL)
	{
		lights_quantity++;
		if (1)//добавить условие на тень
			result = rgbs_adding(result, rgb_multiplying(light->rgb_norm, 1));
			//добавить умножение на интенсивность от нормали
		light = light->next;
	}
	return (create_color(figure->rgb, rgb_dividing(result, lights_quantity)));
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
