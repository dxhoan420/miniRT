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
	struct s_figure	*triangle;

	triangle = get_last_figure_of_scene(scene, rgb);
	triangle->type = TRIANGLE;
	triangle->get_distance = distance_to_triangle;
	triangle->first = one;
	triangle->second = two_three.src;
	triangle->third = two_three.dir;
}

//origin by Oumar Mimouni aka omimouni, remake by me DXhoan
void	get_vertex(t_vec center, t_vec normal, float size, t_vec *vertex)
{
	t_vec	horizontal;
	t_vec	vertical;
	t_vec	start;

	if (normal.x == 0)
		start = create_vector(1, 0, 0);
	else
		start = create_vector(0, 1, 0);
	horizontal = vector_norm(vecs_cross(normal, start));
	vertical = vector_norm(vecs_cross(horizontal, normal));
	vertex[0] = vecs_add(vecs_add(vec_multi(vertical, size / 2), center),
					  vec_multi(horizontal, size / 2));
	vertex[1] = vecs_add(vertex[0], vec_multi(vertical, -size));
	vertex[2] = vecs_add(vertex[1], vec_multi(horizontal, -size));
	vertex[3] = vecs_add(vertex[2], vec_multi(vertical, size));
}

float	distance_to_square(t_ray ray, struct s_figure *square)
{
	t_vec 			vertex[4];
	float			distance;
	struct s_figure triangle;

	get_vertex(square->first, square->normal, square->radius_or_size, vertex);
	triangle.first = vertex[0];
	triangle.second = vertex[1];
	triangle.third = vertex[2];
	distance = distance_to_triangle(ray, &triangle);
	if (distance > FLT_EPSILON)
		return (distance);
	triangle.first = vertex[2];
	triangle.second = vertex[3];
	triangle.third = vertex[0];

	distance = distance_to_triangle(ray, &triangle);
	if (distance > FLT_EPSILON)
		return (distance);
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
