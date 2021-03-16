//
// Created by Demeter Xhoan on 3/14/21.
//

#include "../hdrs/get_pixel_color.h"

t_rgb			compute_diffuse_color(t_vector light_ray,
									   t_rgb rgb_norm, t_rgb color, t_vector normal)
{
	float norm_dot_light;
	float ratio;

	norm_dot_light = vecs_dot(normal, light_ray);
	if (norm_dot_light > 0)
	{
		ratio = norm_dot_light / (vec_length(normal) * vec_length(light_ray));
		return (rgbs_addition(color, rgb_multiply(rgb_norm, ratio)));
	}
	return (color);
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

t_rgb		compute_specular_color(t_ray light_n_view_dir, t_vector normal,
									t_rgb rgb_norm, t_rgb color)
{
	t_vector half_way_dir;
	t_vector light_dir;
	t_vector view_dir;
	float spec;

	light_dir = light_n_view_dir.src;
	view_dir = light_n_view_dir.dir;
	half_way_dir = vector_norm(vecs_add(light_dir, view_dir));
	spec = vecs_dot(normal, half_way_dir);
	if (spec > 0)
	{
		spec = powf(spec, SHINE);
		return (rgbs_addition(color, rgb_multiply(rgb_norm, spec)));
	}
	return (color);
}

int				get_pixel_color(t_all scene, t_ray ray)
{
	struct s_figure *figure;
	t_rgb			light_color;
	t_vector 		light_dir;

	figure = get_figure(ray, scene.figures, CLOSER);
	if (figure == NULL)
		return (0);
	light_color = scene.ambient_rgb_norm;
	while (scene.lights != NULL)
	{
		light_dir = vecs_subtraction(scene.lights->src, figure->hit);
		if (1)
//		if (!is_shaded(scene.figures, figure->hit, light_dir))
		{
			light_color = compute_diffuse_color(vector_norm(light_dir),
							scene.lights->rgb_norm, light_color, figure->normal);
//			light_color = compute_specular_color(create_ray(
//						vector_norm(light_dir),vector_norm(
//						vecs_subtraction(ray.src, figure->hit))),
//					 figure->normal,scene.lights->rgb_norm,light_color);
		}
		scene.lights = scene.lights->next;
	}
	return (create_color(figure->rgb, light_color));
}