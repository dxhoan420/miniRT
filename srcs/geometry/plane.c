//
// Created by Demeter Xhoan on 3/10/21.
//

#include "../../hdrs/miniRT.h"

float	distance_to_plane(t_ray ray, struct s_figure *plane)
{
	float		norm_dot_cam_dir;
	t_vec		from_cam_to_plane;
	float		distance;

	norm_dot_cam_dir = vecs_dot(ray.dir, plane->normal);
	if (fabsf(norm_dot_cam_dir) < FLT_EPSILON)
		return (0);
	from_cam_to_plane = vecs_subtraction(plane->first, ray.src);
	distance = vecs_dot(from_cam_to_plane, plane->normal) / norm_dot_cam_dir;
	if (distance > FLT_EPSILON)
	{
		if (norm_dot_cam_dir > 0)
			plane->normal = vec_multi(plane->normal, -1);
		return (distance);
	}
	return (0);
}

void	add_plane(t_all *scene, t_vec point, t_vec norm, t_rgb rgb)
{
	struct s_figure	*plane;

	plane = get_last_figure_of_scene(scene, rgb);
	plane->type = PLANE;
	plane->get_distance = distance_to_plane;
	plane->first = point;
	plane->normal = vector_norm(norm);
}
