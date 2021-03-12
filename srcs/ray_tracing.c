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

void			set_values(struct s_figure *figure, float dist, t_ray ray)
{
	t_vector normal;

	figure->dist = dist;
	figure->crossing = vecs_add(ray.src, vec_multi(ray.dir, figure->dist));
	normal = vector_norm(vecs_subtraction(figure->crossing,
										  figure->first_or_center));
	if (figure->side == OUTER)
		figure->normal = normal;
	else
		figure->normal = vec_multi(normal, -1);
}

struct s_figure	*get_figure(t_ray ray, t_figures *figures, int first_or_closer)
{
	struct s_figure *closer_one = NULL;
	float 			minimum_positive = MAXFLOAT;
	float			distance;

	while (figures != NULL)
	{
		if (figures->id == SPHERE)
			distance = distance_to_sphere(ray, figures);
		if (first_or_closer == FIRST && distance > FLT_EPSILON)
			return (NULL);
		if (distance > FLT_EPSILON && distance < minimum_positive)
		{
			minimum_positive = distance;
			closer_one = figures;
		}
		figures = figures->next;
	}
	if (closer_one != NULL)
		set_values(closer_one, minimum_positive, ray);
	return(closer_one);
}

t_rgb			compute_diffuse_color(t_vector light_ray,
						struct s_light light, t_rgb color, t_vector normal)
{
	float norm_dot_light;
	float ratio;

	norm_dot_light = vecs_dot(normal, light_ray);
	if (norm_dot_light < 0)
		return (color);
	ratio = norm_dot_light / (vec_length(normal) * vec_length(light_ray));
	return (rgbs_addition(color, rgb_multiply(light.rgb_norm, ratio)));
}

int				is_shaded(t_figures *figures, t_vector crossing,
				 t_vector light_ray)
{
	while (figures != NULL)
	{
		if (get_figure(create_ray(crossing, light_ray), figures, FIRST) != NULL)
			return (1);
		figures = figures->next;
	}
	return (0);
}

int				get_pixel_color(t_all scene, t_ray ray)
{
	struct s_figure *figure;
	t_rgb			light_color;
	t_vector 		light_ray;

	figure = get_figure(ray, scene.figures, CLOSER);
	if (figure == NULL)
		return (0);
	light_color = scene.ambient_rgb_norm;
	while (scene.lights != NULL)
	{
		light_ray = vecs_subtraction(scene.lights->src, figure->crossing);
//		if (1)
		if (!is_shaded(scene.figures, figure->crossing, light_ray))
			light_color = compute_diffuse_color(light_ray, *(scene.lights),
												light_color, figure->normal);
		scene.lights = scene.lights->next;
	}
	return (create_color(figure->rgb, light_color));
}

void			render_scene(void *mlx, void *window, t_all scene)
{
	int			mlx_x;
	int 		mlx_y;
	t_ray 		ray;
	t_viewport	viewport;

	viewport = get_viewport(scene.x_resolution, scene.y_resolution,
						 scene.camera.field_of_view);
	ray.src = scene.camera.coordinates;
	ray.dir.z = 1;//вот эту хуйню поменять надо!
	ray.dir.y = (float)scene.y_resolution / 2 * viewport.y_pixel;
	mlx_y = 0;
	while (mlx_y < scene.y_resolution)
	{
		ray.dir.x = (-(float)scene.x_resolution / 2) * viewport.x_pixel;
		mlx_x = 0;
		while (mlx_x < scene.x_resolution)
		{
			mlx_pixel_put(mlx, window, mlx_x, mlx_y, get_pixel_color(scene, ray));
			ray.dir.x += viewport.x_pixel;
			mlx_x++;
		}
		ray.dir.y -= viewport.y_pixel;
		mlx_y++;
	}
}
