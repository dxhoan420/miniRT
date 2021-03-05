//
// Created by Demeter Xhoan on 2/20/21.
//

#include "../headers/miniRT.h"

t_all	add_sphere(t_all scene, t_vector coordinates, float diameter, int color)
{
	t_figures *iterator = scene.figures;
	struct s_figure *new;

	new = malloc(sizeof (struct s_figure));
	if (new == NULL)
		exit(-1);
	new->id	= SPHERE;
	new->first_or_center = coordinates;
	new->radius_or_size = diameter / 2;
	new->color = color;
	new->next = NULL;
	if (iterator != NULL)
	{
		while (iterator->next != NULL)
			iterator = iterator->next;
		iterator->next = new;
	}
	else
		scene.figures = new;
	return (scene);
}

float		distance_to_sphere(t_vector source_of_ray, t_vector ray,
								struct s_figure sphere)
{
	float a;
	float b;
	float c;
	float discriminant;
	float distance;

	t_vector cam_to_center;

	cam_to_center = vectors_subtraction(source_of_ray, sphere
			.first_or_center);
	a = vectors_dot_product(ray, ray);
	b = 2 * (vectors_dot_product(cam_to_center, ray));
	c = vectors_dot_product(cam_to_center, cam_to_center) -
		(sphere.radius_or_size * sphere.radius_or_size);
	discriminant = b * b - 4 * c * a;
	if (discriminant < 0)
		return (0);
	distance = (-b - sqrtf(discriminant)) / 2; //что тут блять правильно
	// сделать надо плюс или минус ебать его налево
	if (distance < 0)
		distance = (-b + sqrtf(discriminant)) / 2;
	return (distance);
}