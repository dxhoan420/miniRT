//
// Created by Demeter Xhoan on 3/19/21.
//

#include "miniRT.h"

float	limit_height(float distance, struct s_figure cylinder, t_ray ray)
{
	t_vec	crossing;
	t_vec	opposite;

	if (distance < 0)
		return (-1);
	opposite = vecs_add(cylinder.first,
			 vec_multi(cylinder.second, cylinder.height));
	crossing = vecs_add(ray.src, vec_multi(ray.dir, distance));
	if (vecs_dot(cylinder.second,
			  vecs_subtraction(crossing, cylinder.first)) <= 0)
		return (-1);
	if (vecs_dot(cylinder.second, vecs_subtraction(crossing, opposite)) >= 0)
		return (-1);
	return (distance);
}

int	set_roots(t_vec params, float *x0, float *x1)
{
	float	discriminant;
	float	hueta;

	discriminant = params.y * params.y - 4 * params.x * params.z;
	if (discriminant < 0)
		return (0);
	if (discriminant == 0)
	{
		*x0 = -params.y / (2 * params.x);
		*x1 = *x0;
		return (1);
	}
	if (params.y > 0)
		hueta = -1 * (params.y + sqrtf(discriminant)) / 2;
	else
		hueta = -1 * (params.y - sqrtf(discriminant)) / 2;
	*x0 = hueta / params.x;
	*x1 = params.z / hueta;
	return (1);
}

int	find_roots(float *t0, float *t1, struct s_figure *cylinder, t_ray ray)
{
	t_vec	a_sqrt;
	t_vec	right;
	float	a;
	float	b;
	float	c;

	a_sqrt = vecs_subtraction(ray.dir, vec_multi(cylinder->second,
				 vecs_dot(ray.dir, cylinder->second)));
	a = vecs_dot(a_sqrt, a_sqrt);
	right = vecs_subtraction(vecs_subtraction(ray.src, cylinder->first),
			 vec_multi(cylinder->second, vecs_dot(vecs_subtraction(ray.src,
						cylinder->first), cylinder->second)));
	b = 2 * vecs_dot(a_sqrt, right);
	c = vecs_dot(right, right)
		- (cylinder->rad_or_size * cylinder->rad_or_size);
	return (set_roots(create_vector(a, b, c), t0, t1));
}

float	distance_to_cylinder(t_ray ray, struct s_figure *cylinder)
{
	float	t0;
	float	t1;

	if (!find_roots(&t0, &t1, cylinder, ray))
		return (0);
	t0 = limit_height(t0, *cylinder, ray);
	t1 = limit_height(t1, *cylinder, ray);
	if (t0 < 0 && t1 < 0)
		return (0);
	if (t1 < t0 && t1 > 0)
		return (t1);
	if (t0 > 0)
		return (t0);
	return (t1);
}

void	add_cylinder(t_all *scene, t_ray one_two, t_vec d_n_h, t_rgb rgb)
{
	struct s_figure	*cylinder;

	cylinder = get_last_figure_of_scene(scene, rgb);
	cylinder->type = CYLINDER;
	cylinder->get_distance = distance_to_cylinder;
	cylinder->first = one_two.src;
	cylinder->second = vector_norm(one_two.dir);
	cylinder->rad_or_size = d_n_h.x / 2;
	cylinder->height = d_n_h.y;
}
