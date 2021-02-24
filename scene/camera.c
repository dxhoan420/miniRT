//
// Created by Demeter Xhoan on 2/20/21.
//

#include "../headers/miniRT.h"

int		add_camera(t_all scene, t_vector coordinates, t_vector norma_vector,
				int field_of_view)
{
	static int result 	= 0;
	t_cameras *iterator = scene.cameras;
	t_cameras *new;
	if (!(new = malloc(sizeof (t_cameras))))
		exit(-1);
	result++;
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
	return (result);
}