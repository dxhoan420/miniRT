//
// Created by Demeter Xhoan on 3/16/21.
//

#include "../../hdrs/miniRT.h"

//by Tomas Möller & Ben Trumbore
float distance_to_triangle(t_ray ray, struct s_figure *triangle)
{
	t_vec edge_1;
	t_vec edge_2;
	t_vec pvec;
	t_vec tvec;
	t_vec det;

	edge_1 = vecs_subtraction(triangle->second, triangle->first);
	edge_2 = vecs_subtraction(triangle->third, triangle->first);
	pvec = vecs_cross(ray.dir, edge_2);
	det.x = vecs_dot(edge_1, pvec);
	if (det.x < 1e-8 && det.x > -1e-8)
		return 0;
	det.x = 1 / det.x;
	tvec = vecs_subtraction(ray.src, triangle->first);
	det.y = vecs_dot(tvec, pvec) * det.x;
	if (det.y < 0 || det.y > 1)
		return (0);
	tvec = vecs_cross(tvec, edge_1);
	det.z = vecs_dot(ray.dir, tvec) * det.x;
	if (det.z < 0 || det.y + det.z > 1)
		return (0);
	return (vecs_dot(edge_2, tvec) * det.x);
}

void	add_triangle(t_all *scene, t_vec one, t_ray two_three, t_rgb rgb)
{
	struct s_figure *triangle;

	triangle = get_last_figure_of_scene(scene, rgb);
	triangle->type = TRIANGLE;
	triangle->get_distance = distance_to_triangle;
	triangle->first = one;
	triangle->second = two_three.src;
	triangle->third = two_three.dir;
}