//
// Created by Demeter Xhoan on 3/10/21.
//

#include "../../hdrs/miniRT.h"

float	distance_to_plane(t_ray ray, struct s_figure *plane)
{
	float norm_dot_light;
	t_vector from_cam_to_plane;
	float distance;

	norm_dot_light = vecs_dot(ray.dir, plane->normal);
	if (fabsf(norm_dot_light) < FLT_EPSILON)
		return (0);
	from_cam_to_plane = vecs_subtraction(plane->first, ray.src);
	distance = vecs_dot(from_cam_to_plane, plane->normal) / norm_dot_light;
	if (distance > FLT_EPSILON)
	{
		if (norm_dot_light > 0)
			plane->normal = vec_multi(plane->normal, -1);
		return (distance);
	}
	return (0);
}

void	add_plane(t_all *scene, t_vector coordinates, t_vector norm, t_rgb rgb)
{
	t_figures *iterator;
	struct s_figure *new;

	iterator = scene->figures;
	new = malloc(sizeof (struct s_figure));
	if (new == NULL)
		exit(-1);
	new->type = PLANE;
	new->get_distance = distance_to_plane;
	new->first = coordinates;
	new->normal = vector_norm(norm);
	new->rgb = rgb;
	new->next = NULL;
	if (iterator != NULL)
	{
		while (iterator->next != NULL)
			iterator = iterator->next;
		iterator->next = new;
	}
	else
		scene->figures = new;
}
