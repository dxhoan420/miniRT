//
// Created by Demeter Xhoan on 2/20/21.
//

#include "../headers/miniRT.h"

int		add_sphere(t_all scene, t_vector coordinates, float diameter, int color)
{
	static int result 	= 0;
	t_spheres *iterator = scene.spheres;
	t_spheres *new;
	if (!(new = malloc(sizeof (t_spheres))))
		exit(-1);
	result++;
	new->coordinates	= coordinates;
	new->diameter 		= diameter;
	new->color 			= color;
	new->next			= NULL;
	if (iterator != NULL)
	{
		while (iterator->next != NULL)
			iterator = iterator->next;
		iterator->next = new;
	}
	else
		scene.spheres = new;
	return (result);
}

float		distance_to_sphere(struct s_camera camera, t_vector ray,
		struct s_sphere sphere)
{
	float b;
	float c;
	float discriminant;
	float distance;
	t_vector from_cam_to_sphere;

	from_cam_to_sphere = subtraction_of_vectors(camera.coordinates, sphere
			.coordinates);
	b = 2 * (multiplication_of_vectors(from_cam_to_sphere, ray));
	c = multiplication_of_vectors(from_cam_to_sphere, from_cam_to_sphere) -
		(sphere.diameter / 2 * sphere.diameter / 2);
	discriminant = b * b - 4 * c;
	if (discriminant < 0)
		return (0);
	distance = (-b - sqrt(discriminant)) / 2;
	printf("second distance = : %f", (-b + sqrt(discriminant)) / 2);
}