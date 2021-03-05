//
// Created by Demeter Xhoan on 2/20/21.
//

#include "../headers/miniRT.h"

t_all	add_camera(t_all scene, t_vector coordinates, t_vector norma_vector,
				int field_of_view)
{
	t_cameras *iterator = scene.cameras;
	t_cameras *new;
	if (!(new = malloc(sizeof (t_cameras))))
		exit(-1);
	new->coordinates	= coordinates;
	new->norma_vector 	= norma_vector;
	new->field_of_view	= field_of_view;
	new->next 			= NULL;
	if (iterator != NULL)
	{
		while (iterator->next != NULL)
			iterator = iterator->next;
		iterator->next = new;
	}
	else
		scene.cameras = new;
	return (scene);
}

t_all	add_light(t_all scene, t_vector coordinates, float light_ratio,
				int light_color)
{
	t_lights *iterator = scene.lights;
	struct s_light *new;

	new = malloc(sizeof(struct s_light));
	if (new == NULL)
		exit(-1);
	new->coordinates = coordinates;
	new->light_ratio = light_ratio;
	new->light_color = light_color;
	new->next = NULL;
	if (iterator != NULL)
	{
		while (iterator->next != NULL)
			iterator = iterator->next;
		iterator->next = new;
	}
	else
		scene.lights = new;
	return (scene);
}