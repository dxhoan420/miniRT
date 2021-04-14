//
// Created by Demeter Xhoan on 3/19/21.
//

#include "miniRT.h"

void	check_t(float *t, struct s_figure cylinder, t_ray ray)
{
	t_vec	q;
	t_vec	p2;

	p2 = vecs_add(cylinder.first, vec_multi(cylinder.second, cylinder.height));
	q = vecs_add(ray.src, vec_multi(ray.dir, *t));
	if (vecs_dot(cylinder.second, vecs_subtraction(q, cylinder.first)) <= 0)
		*t = -1;
	if (vecs_dot(cylinder.second, vecs_subtraction(q, p2)) >= 0)
		*t = -1;
}

int	solve_quadratic(t_vec params, float *x0, float *x1)
{
	float	discr;
	float	q;
	float	buffer;

	discr = powf(params.y, 2) - 4 * params.x * params.z;
	if (discr < 0)
		return (0);
	else if (discr == 0)
	{
		*x0 = -0.5f * params.y / params.x;
		*x1 = -0.5f * params.y / params.x;
	}
	else
	{
		if (params.y > 0)
			q = -1 * (params.y + sqrtf(discr)) / 2;
		else
			q = -1 * (params.y - sqrtf(discr)) / 2;
		*x0 = q / params.x;
		*x1 = params.z / q;
	}
	if (*x0 > *x1)
	{
		buffer = *x0;
		*x0 = *x1;
		*x1 = buffer;
	}
	return (1);
}

int	cyl_get_roots(float *t0, float *t1, struct s_figure *cylinder, t_ray ray)
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
	if (!solve_quadratic(create_vector(a, b, c), t0, t1))
		return (0);
	return (1);
}

float	distance_to_cylinder(t_ray ray, struct s_figure *cylinder)
{
	float	t0;
	float	t1;

	if (!cyl_get_roots(&t0, &t1, cylinder, ray))
		return (0);
	if (t0 > 0)
		check_t(&t0, *cylinder, ray);
	if (t1 > 0)
		check_t(&t1, *cylinder, ray);
	if (t0 < 0 && t1 < 0)
		return (0);
	if (t1 < t0)
	{
		if (t1 > 0)
			return (t1);
		else
			return (t0);
	}
	else
	{
		if (t0 > 0)
			return (t0);
		else
			return (t1);
	}
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
