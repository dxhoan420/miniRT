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
	struct s_figure	*new;

	new = get_last_figure_of_scene(scene, rgb);
	new->type = PLANE;
	new->get_distance = distance_to_plane;
	new->first = point;
	new->normal = vector_norm(norm);
}

float	distance_to_square(t_ray ray, struct s_figure *square)
{
	float distance;
	float half_of_size;

	distance = distance_to_plane(ray, square);
	if (distance > 0)
	{
		half_of_size = square->radius_or_size / 2;
		square->hit = vecs_add(ray.src, vec_multi(ray.dir, distance
							   * (1 - FLT_EPSILON * SHADOW_NOISE_REDUCTION)));
		if (fabsf(square->hit.x - square->first.x) <= half_of_size &&
				fabsf(square->hit.y - square->first.y) <= half_of_size &&
				fabsf(square->hit.z - square->first.z) <= half_of_size)
			return (distance);
	}
	return (0);
}

void	add_square(t_all *scene, t_ray cntr_n_nrm, float size, t_rgb rgb)
{
	struct s_figure *square;

	square = get_last_figure_of_scene(scene, rgb);
	square->type = SQUARE;
	square->get_distance = distance_to_square;
	square->first = cntr_n_nrm.src;
	square->normal = vector_norm(cntr_n_nrm.dir);
	square->radius_or_size = size;
}
