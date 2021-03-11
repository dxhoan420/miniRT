//
// Created by Demeter Xhoan on 2/20/21.
//

#include "../hdrs/miniRT.h"

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

t_all	add_light(t_all scene, t_vector coordinates, t_rgb rgb_norm)
{
	t_lights *iterator = scene.lights;
	struct s_light *new;

	new = malloc(sizeof(struct s_light));
	if (new == NULL)
		exit(-1);
	new->src = coordinates;
	new->rgb_norm = rgb_norm;
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