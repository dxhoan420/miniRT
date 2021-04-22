//
// Created by Demeter Xhoan on 3/14/21.
//

#include "get_pixel_color.h"

t_vec	get_normal(struct s_figure figure)
{
	t_vec			m;
	t_vec			normal;
	struct s_figure	cylinder;
	struct s_figure	triangle;

	if (figure.type == CYLINDER)
	{
		cylinder = figure;
		m = vecs_subtraction(cylinder.hit, cylinder.first);
		normal = vector_norm(vecs_subtraction(m, vec_multi(cylinder.second,
								   vecs_dot(cylinder.second, m))));
	}
	if (figure.type == TRIANGLE)
	{
		triangle = figure;
		normal = vector_norm(vecs_cross(
				vecs_subtraction(triangle.second, triangle.first),
				vecs_subtraction(triangle.third, triangle.first)));
	}
	return (normal);
}

void	set_values(struct s_figure *figure, float dist, t_ray ray)
{
	t_vec	normal;

	figure->hit = vecs_add(ray.src, vec_multi(ray.dir, dist
				* (1 - FLT_EPSILON * SHADOW_NOISE_REDUCTION)));
	if (figure->type == SPHERE)
	{
		normal = vector_norm(vecs_subtraction(figure->hit, figure->first));
		if (figure->side == OUTER)
			figure->normal = normal;
		else
			figure->normal = vec_multi(normal, -1);
	}
	if (figure->type == TRIANGLE || figure->type == CYLINDER)
	{
		normal = get_normal(*figure);
		if (vecs_dot(ray.dir, normal) > 0)
			figure->normal = vec_multi(normal, -1);
		else
			figure->normal = normal;
	}
	if (figure->type == SQUARE && vecs_dot(ray.dir, figure->normal) > 0)
		figure->normal = vec_multi(figure->normal, -1);
}

struct s_figure	*get_figure(t_ray ray, t_figures *figures, int first_or_closer)
{
	struct s_figure	*closer_one;
	float			minimum_positive;
	float			distance;

	closer_one = NULL;
	minimum_positive = MAXFLOAT;
	while (figures != NULL)
	{
		distance = figures->get_distance(ray, figures);
		if (first_or_closer == FIRST && distance > FLT_EPSILON)
		{
			if (distance < 1)
				return (figures);
		}
		else if (distance > FLT_EPSILON && distance < minimum_positive)
		{
			minimum_positive = distance;
			closer_one = figures;
		}
		figures = figures->next;
	}
	if (closer_one != NULL)
		set_values(closer_one, minimum_positive, ray);
	return (closer_one);
}

struct s_figure	*get_last_figure_of_scene(t_all *scene, t_rgb rgb)
{
	t_figures		*iterator;
	struct s_figure	*new;

	iterator = scene->figures;
	new = malloc(sizeof (struct s_figure));
	if (new == NULL)
		exit(-666);
	new->next = NULL;
	new->rgb = rgb;
	if (iterator != NULL)
	{
		while (iterator->next != NULL)
			iterator = iterator->next;
		iterator->next = new;
	}
	else
		scene->figures = new;
	return (new);
}
