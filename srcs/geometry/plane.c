//
// Created by Demeter Xhoan on 3/10/21.
//

#include "../../hdrs/miniRT.h"

float	distance_to_plane(t_ray ray, struct s_figure *plane)
{
	float		norm_dot_light;
	t_vec		from_cam_to_plane;
	float		distance;

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

void	add_plane(t_all *scene, t_vec point, t_vec norm, t_rgb rgb)
{
	struct s_figure	*new;

	new = get_last_figure_of_scene(scene, rgb);
	new->type = PLANE;
	new->get_distance = distance_to_plane;
	new->first = point;
	new->normal = vector_norm(norm);
}
