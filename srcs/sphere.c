//
// Created by Demeter Xhoan on 2/20/21.
//

#include "../hdrs/miniRT.h"

void	add_sphere(t_all *scene, t_vector center, float diameter, t_rgb rgb)
{
	t_figures *iterator = scene->figures;
	struct s_figure *new;

	new = malloc(sizeof (struct s_figure));
	if (new == NULL)
		exit(-1);
	new->id	= SPHERE;
	new->first_or_center = center;
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

float		distance_to_sphere(t_ray ray, struct s_figure sphere)
{
	float a;
	float b;
	float c;
	float discriminant;
	float distance;

	t_vector cam_to_center;

	cam_to_center = vecs_subtraction(ray.src, sphere
			.first_or_center);
	a = vecs_dot_product(ray.dir, ray.dir);
	b = 2 * (vecs_dot_product(cam_to_center, ray.dir));
	c = vecs_dot_product(cam_to_center, cam_to_center) -
		(sphere.radius_or_size * sphere.radius_or_size);
	discriminant = b * b - 4 * c * a;
	if (discriminant < 0)
		return (0);
	distance = (-b - sqrtf(discriminant)) / 2;
	if (distance < 0)
		distance = (-b + sqrtf(discriminant)) / 2;
	return (distance);
}