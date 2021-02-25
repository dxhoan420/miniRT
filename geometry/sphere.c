//
// Created by Demeter Xhoan on 2/20/21.
//

#include "../headers/miniRT.h"

t_all	add_sphere(t_all scene, t_vector coordinates, float diameter, int color)
{
	static int result 	= 0;
	t_spheres *iterator = scene.spheres;
	t_spheres *new;
	if (!(new = malloc(sizeof (t_spheres))))
		exit(-1);
	result++;
	new->coordinates	= coordinates;
	new->radius 		= diameter / 2;
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
	return (scene);
}

float		distance_to_sphere(struct s_camera camera, t_vector ray,
		struct s_sphere sphere)
{
	float a;
	float b;
	float c;
	float discriminant;
	float distance;

	t_vector cam_to_center;

	cam_to_center = subtraction_vectors(camera.coordinates, sphere
			.coordinates);
	a = dot_product_of_vectors(ray, ray);
	b = 2 * (dot_product_of_vectors(cam_to_center, ray));
	c = dot_product_of_vectors(cam_to_center, cam_to_center) -
		(sphere.radius * sphere.radius);
	discriminant = b * b - 4 * c * a;
	if (discriminant < 0)
		return (0);
	distance = (-b - sqrt(discriminant)) / 2;
	if (distance < 0)
		distance = (-b + sqrt(discriminant)) / 2;
	//printf("first distance	= : %f\n", distance);
	//printf("second distance	= : %f\n", (-b + sqrt(discriminant)) / 2);
	//printf("%f %f %f\n", cam_to_center.x, cam_to_center.y, cam_to_center.z);
	return (distance);
}