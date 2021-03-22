//
// Created by Demeter Xhoan on 3/14/21.
//

#include "get_pixel_color.h"

//t_vec	set_cylinder_normal(struct s_figure cylinder)
//{
//	t_vec	pc;
//	t_vec	n;
//	float	h;
//
//	pc = vecs_subtraction(cylinder.hit, cylinder.first);
//	h = vecs_dot(pc, cylinder.second);
//	n = vecs_subtraction(pc, vec_multi(cylinder.second, h));
//	return (vector_norm(n));
//}

t_vec 		get_cylinder_normal(struct s_figure cylinder)
{
	t_vec ctp;
	t_vec normal;

	ctp = vecs_subtraction(cylinder.hit, cylinder.first);
	normal = vecs_subtraction(ctp, vec_multi(cylinder.second,
										vecs_dot(cylinder.second, ctp)));
	return (vector_norm(normal));
}

//should replace normal computing in add_triangle;
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
		if (figure->type == CYLINDER)
			normal = get_cylinder_normal(*figure);
		else
			normal = vector_norm(vecs_cross(
				vecs_subtraction(figure->second, figure->first),
				vecs_subtraction(figure->third, figure->first)));
		if (vecs_dot(ray.dir, normal) > 0)
			figure->normal = vec_multi(normal, -1);
		else
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
