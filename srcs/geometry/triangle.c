//
// Created by Demeter Xhoan on 3/16/21.
//

#include "../../hdrs/miniRT.h"

float		check_edge(t_vector second, t_vector first, t_vector normal,
				t_vector crossing)
{
	t_vector edge = vecs_subtraction(second, first);
	t_vector from_point_to_cross = vecs_subtraction(crossing, first);
	t_vector cross = vecs_cross(edge, from_point_to_cross);
	return (vecs_dot(normal, cross));
}

float	distance_to_triangle(t_ray ray, struct s_figure *trngl)
{
	float distance;
	float norm_dot_dir;
	float norm_dot_first;

	trngl->normal = vector_norm(vecs_cross(
			vecs_subtraction(trngl->second, trngl->first),
			vecs_subtraction(trngl->third, trngl->first)));
	norm_dot_dir = vecs_dot(trngl->normal, ray.dir);
	if (fabsf(norm_dot_dir) < FLT_EPSILON)
		return (0);
	norm_dot_first = vecs_dot(trngl->normal, trngl->first);
	distance = -(vecs_dot(trngl->normal, ray.src) + norm_dot_first) /
			vecs_dot(trngl->normal, ray.dir);
	if (distance < 0)
		return (0);
	if (check_edge(trngl->second, trngl->first, trngl->normal, trngl->hit) < 0
	|| check_edge(trngl->third, trngl->second, trngl->normal, trngl->hit) < 0
	|| check_edge(trngl-> first, trngl->third, trngl->normal, trngl->hit) < 0)
		return (0);
	return (distance);
}

void	add_triangle(t_all *scene, t_vector first, t_ray second_n_third, t_rgb
rgb)
{
	t_figures *iterator;
	struct s_figure *new;

	iterator = scene->figures;
	new = malloc(sizeof (struct s_figure));
	if (new == NULL)
		exit(-1);
	new->type = TRIANGLE;
	new->get_distance = distance_to_triangle;
	new->first = first;
	new->second = second_n_third.src;
	new->third = second_n_third.dir;
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