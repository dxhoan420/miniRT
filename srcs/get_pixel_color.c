//
// Created by Demeter Xhoan on 3/14/21.
//

#include "../hdrs/get_pixel_color.h"

t_rgb	diffuse_color(struct s_light light, t_rgb color, t_vec normal)
{
	float	norm_dot_light;
	float	ratio;

	norm_dot_light = vecs_dot(normal, light.dir);
	if (norm_dot_light > 0)
	{
		ratio = norm_dot_light / (vec_length(normal) * vec_length(light.dir));
		return (rgbs_addition(color, rgb_multiply(light.rgb_norm, ratio)));
	}
	return (color);
}

t_rgb	compute_specular_color(struct s_light light, t_vec normal, t_rgb color,
		t_vec view_dir)
{
	t_vec	half_way_dir;
	float	spec;

	view_dir = vector_norm(view_dir);
	light.dir = vector_norm(light.dir);
	half_way_dir = vector_norm(vecs_add(light.dir, view_dir));
	spec = vecs_dot(normal, half_way_dir);
	if (spec > 0)
	{
		spec = powf(spec, SHINE);
		return (rgbs_addition(color, rgb_multiply(light.rgb_norm, spec)));
	}
	return (color);
}

int	is_shaded(t_figures *figures, t_vec crossing, t_vec light_ray)
{
	while (figures != NULL)
	{
		if (get_figure(create_ray(crossing, light_ray), figures, FIRST) != NULL)
			return (1);
		figures = figures->next;
	}
	return (0);
}

t_rgb	get_light_color(struct s_light light, struct s_figure figure,
		t_rgb color, t_ray ray)
{
	t_vec	view_dir;

	view_dir = vecs_subtraction(ray.src, figure.hit);
	color = diffuse_color(light, color, figure.normal);
	color = compute_specular_color(light, figure.normal, color, view_dir);
	return (color);
}

int	get_pixel_color(t_all scene, t_ray ray)
{
	struct s_figure	*figure;
	t_rgb			color;
	struct s_light	light;

	figure = get_figure(ray, scene.figures, CLOSER);
	if (figure == NULL)
		return (0);
	color = scene.ambient_rgb_norm;
	while (scene.lights != NULL)
	{
		light.src = scene.lights->src;
		light.rgb_norm = scene.lights->rgb_norm;
		light.dir = vecs_subtraction(light.src, figure->hit);
		if (!is_shaded(scene.figures, figure->hit, light.dir))
			color = get_light_color(light, *figure, color, ray);
		scene.lights = scene.lights->next;
	}
	return (create_color(figure->rgb, color));
}
