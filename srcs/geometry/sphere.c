//
// Created by Demeter Xhoan on 2/20/21.
//

#include "../../hdrs/miniRT.h"

float		distance_to_sphere(t_ray ray, struct s_figure *sphere)
{
	t_vector cam_to_center;
	t_vector nums;
	float discriminant;
	float distance;

	cam_to_center = vecs_subtraction(ray.src, sphere->first);
	nums.x = vecs_dot(ray.dir, ray.dir);
	nums.y = 2 * (vecs_dot(cam_to_center, ray.dir));
	nums.z = vecs_dot(cam_to_center, cam_to_center) -
			 (sphere->radius_or_size * sphere->radius_or_size);
	discriminant = nums.y * nums.y - 4 * nums.z * nums.x;
	if (discriminant < 0)
		return (0);
	distance = (-nums.y - sqrtf(discriminant)) / (2 * nums.x);
	if (distance < 0)
	{
		distance = (-nums.y + sqrtf(discriminant)) / (2 * nums.x);
		sphere->side = INNER;
	} else
		sphere->side = OUTER;
	return (distance);
}

void	add_sphere(t_all *scene, t_vector center, float diameter, t_rgb rgb)
{
	t_figures *iterator;
	struct s_figure *new;

	iterator = scene->figures;
	new = malloc(sizeof (struct s_figure));
	if (new == NULL)
		exit(-1);
	new->type	= SPHERE;
	new->get_distance = distance_to_sphere;
	new->first = center;
	new->radius_or_size = diameter / 2;
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
