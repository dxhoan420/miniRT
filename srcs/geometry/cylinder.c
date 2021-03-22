//
// Created by Demeter Xhoan on 3/19/21.
//

#include "miniRT.h"

//MWinter remake
//float	set_cylinder_normal(struct s_figure *cylinder, t_ray ray, float
//		dist)
//{
//	t_vec	pc;
//	t_vec	n;
//	float	h;
//
//	cylinder->hit = vecs_add(ray.src, vec_multi(ray.dir, dist
//							   * (1 - FLT_EPSILON * SHADOW_NOISE_REDUCTION)));
//	pc = vecs_subtraction(cylinder->hit, cylinder->first);
//	h = vecs_dot(pc, cylinder->second);
//	n = vecs_subtraction(pc, vec_multi(cylinder->second, h));
//	cylinder->normal = vector_norm(n);
//	return (dist);
//}
//
//int	get_solution(t_vec d, struct s_figure *cylinder, t_vec oc, float *t)
//{
//	t_vec 	h;
//	t_vec 	oc_h;
//	t_vec 	abc;
//	float	dscr;
//
//
//	h = vec_multi(cylinder->second, vecs_dot(d, cylinder->second));
//	h = vecs_subtraction(d, h);
//	oc_h = vec_multi(cylinder->second, vecs_dot(oc, cylinder->second));
//	oc_h = vecs_subtraction(oc, oc_h);
//	abc.x = vecs_dot(h, h);
//	abc.y = 2 * vecs_dot(h, oc_h);
//	abc.z = vecs_dot(oc_h, oc_h) - cylinder->radius_or_size * cylinder->radius_or_size;
//	dscr = abc.y * abc.y - 4 * abc.x * abc.z;
//	if (dscr < 0)
//		return (0);
//	if (dscr == 0)
//	{
//		t[0] = -abc.y / (2 * abc.x);
//		return (1);
//	}
//	t[0] = (-abc.y + sqrtf(dscr)) / (2 * abc.x);
//	t[1] = (-abc.y - sqrtf(dscr)) / (2 * abc.x);
//	return (2);
//}
//
//float	distance_to_cylinder(t_ray ray, struct s_figure *cylinder)
//{
//	t_vec o = ray.src;
//	t_vec d = ray.dir;
//	float	t[2];
//	t_vec 	p[2];
//	float	h[2];
//	t_vec	oc;
//	int 	temp;
//
//	oc = vecs_subtraction(o, cylinder->first);
//	temp = get_solution(d, cylinder, oc, t);
//	if (temp == 0)
//		return (0);
//	else if (temp == 1)
//		return (set_cylinder_normal(cylinder, ray, t[0]));
//	p[0] = vecs_add(o, vec_multi(d, t[0]));
//	h[0] = vecs_dot(cylinder->second, vecs_subtraction(p[0], cylinder->first));
//	p[1] = vecs_add(o, vec_multi(d, t[1]));
//	h[1] = vecs_dot(cylinder->second, vecs_subtraction(p[1], cylinder->first));
//	if (-cylinder->height / 2 <= h[0]
//			&& h[0] <= cylinder->height / 2 && t[0] > 0.001)
//		return (set_cylinder_normal(cylinder, ray, t[0]));;
//	if (-cylinder->height / 2 <= h[1]
//			&& h[1] <= cylinder->height / 2 && t[1] > 0.001)
//		return (set_cylinder_normal(cylinder, ray, t[1]));
//	return (0);
//}

void		check_t(float *t, struct s_figure cylinder, t_ray ray)
{
	t_vec q;
	t_vec p2;

	p2 = vecs_add(cylinder.first, vec_multi(cylinder.second, cylinder.height));
	q = vecs_add(ray.src, vec_multi(ray.dir, *t));
	if (vecs_dot(cylinder.second, vecs_subtraction(q, cylinder.first)) <= 0)
		*t = -1;
	if (vecs_dot(cylinder.second, vecs_subtraction(q, p2)) >= 0)
		*t = -1;
}

int			solve_quadratic(t_vec params, float *x0, float *x1)
{
	float discr;
	float q;
	float buffer;

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

	a_sqrt = vecs_subtraction(ray.dir,vec_multi(cylinder->second,
						   vecs_dot(ray.dir, cylinder->second)));
	a = vecs_dot(a_sqrt, a_sqrt);
	right = vecs_subtraction(vecs_subtraction(ray.src, cylinder->first),
			  vec_multi(cylinder->second, vecs_dot(vecs_subtraction(ray.src,
									   cylinder->first), cylinder->second)));
	b = 2 * vecs_dot(a_sqrt, right);
	c = vecs_dot(right, right) - (cylinder->radius_or_size * cylinder->radius_or_size);
	if (!solve_quadratic(create_vector(a, b, c), t0, t1))
		return (0);
	return (1);
}

float	distance_to_cylinder(t_ray ray, struct s_figure *cylinder)
{
	float t0;
	float t1;

	if (!cyl_get_roots(&t0, &t1, cylinder, ray))
		return (0);
	if (t0 > 0)
		check_t(&t0, *cylinder, ray);
	if (t1 > 0)
		check_t(&t1, *cylinder, ray);
	if (t0 < 0 && t1 < 0)
		return (0);
	if (t1 < t0)
		if (t1 > 0)
			return (t1);
		else
			return (t0);
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
	cylinder->radius_or_size = d_n_h.x / 2;
	cylinder->height = d_n_h.y;
}