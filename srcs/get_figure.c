//
// Created by Demeter Xhoan on 3/14/21.
//

#include "../hdrs/get_pixel_color.h"

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
	if (figure->type == TRIANGLE)
	{
		normal = vector_norm(vecs_cross(
				vecs_subtraction(figure->second, figure->first),
				vecs_subtraction(figure->third, figure->first)));
		if (vecs_dot(ray.dir, normal) > 0)
			figure->normal = vec_multi(normal, -1);
		figure->normal = normal;
	}
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
		exit(-1);
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
