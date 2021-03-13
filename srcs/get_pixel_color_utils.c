//
// Created by Demeter Xhoan on 3/14/21.
//
#include "../hdrs/get_pixel_color.h"

void			set_values(struct s_figure *figure, float dist, t_ray ray)
{
	t_vector normal;

	figure->dist = dist;
	figure->crossing = vecs_add(ray.src, vec_multi(ray.dir,
	   dist * (1 - FLT_EPSILON * SHADOW_NOISE_REDUCTION))); //0.99999f
	if (figure->id == SPHERE)
	{
		normal = vector_norm(vecs_subtraction(figure->crossing,
											  figure->first_or_center));
		if (figure->side == OUTER)
			figure->normal = normal;
		else
			figure->normal = vec_multi(normal, -1);
	}
}

struct s_figure	*get_figure(t_ray ray, t_figures *figures, int first_or_closer)
{
	struct s_figure *closer_one = NULL;
	float 			minimum_positive = MAXFLOAT;
	float			distance;
	float (*get_distance[2])(t_ray, t_figures *) = {distance_to_sphere, distance_to_plane};

	while (figures != NULL)
	{
		distance = get_distance[figures->id](ray, figures);
		if (first_or_closer == FIRST && distance > FLT_EPSILON) //&& distance < INFINITY
		{
			if (distance < 1)
				return (figures);
			else
				return (NULL);
		}
		else if (distance > FLT_EPSILON && distance < minimum_positive) //&& distance < INFINITY
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