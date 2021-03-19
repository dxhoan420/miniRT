//
// Created by Demeter Xhoan on 3/19/21.
//

#include "../../hdrs/miniRT.h"

void	get_solving(t_vec d, struct s_figure *cylinder, t_vec oc, float *t)
{
	t_vec 	h;
	t_vec 	oc_h;
	t_vec 	abc;
	float	dscr;

	h = vec_multi(cylinder->second, vecs_dot(d, cylinder->second));
	h = vecs_subtraction(d, h);
	oc_h = vec_multi(cylinder->second, vecs_dot(oc, cylinder->second));
	oc_h = vecs_subtraction(oc, oc_h);
	abc.x = vecs_dot(h, h);
	abc.y = 2 * vecs_dot(h, oc_h);
	abc.z = vecs_dot(oc_h, oc_h) - powf(cylinder->radius_or_size, 2);
	dscr = powf(abc.y, 2) - 4 * abc.x * abc.z;
	if (dscr < 0)
	{
		t[0] = INFINITY;
		t[1] = INFINITY;
		return;
	}
	if (dscr == 0)
	{
		t[0] = -abc.y / (2 * abc.x);
		t[1] = -abc.y / (2 * abc.x);
		return;
	}
	t[0] = (-abc.y + sqrtf(dscr)) / (2 * abc.x);
	t[1] = (-abc.y - sqrtf(dscr)) / (2 * abc.x);
}

float	distance_to_cylinder(t_ray ray, struct s_figure *cylinder)
{
	t_vec o = ray.src;
	t_vec d = ray.dir;
	float	t[2];
	t_vec 	p[2];
	float	h[2];
	t_vec	oc;

	oc = vecs_subtraction(o, cylinder->first);
	get_solving(d, cylinder, oc, t);
	if (t[0] == INFINITY && t[1] == INFINITY)
		return (INFINITY);
	p[0] = vecs_add(o, vec_multi(d, t[0]));
	h[0] = vecs_dot(cylinder->second, vecs_subtraction(p[0], cylinder->first));
	p[1] = vecs_add(o, vec_multi(d, t[1]));
	h[1] = vecs_dot(cylinder->second, vecs_subtraction(p[1], cylinder->first));
	if (-cylinder->height / 2 <= h[0]
			&& h[0] <= cylinder->height / 2 && t[0] > 0.001)
		return t[0];
	if (-cylinder->height / 2 <= h[1]
			&& h[1] <= cylinder->height / 2 && t[1] > 0.001)
		return t[1];
	return (0);
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