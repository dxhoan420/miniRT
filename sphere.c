//
// Created by Demeter Xhoan on 2/20/21.
//

#include "headers/miniRT.h"

int		add_sphere(t_all scene, t_point coordinates, float diameter, int color)
{
	t_all_figures *iterator = scene.figures;
	t_sphere *new 		= malloc(sizeof (t_sphere));

	new->coordinates	= coordinates;
	new->diameter 		= diameter;
	new->color 			= color;
	if (iterator->current != NULL)
		while (iterator->next != NULL)
			iterator = iterator->next;
	iterator->next = malloc(sizeof (t_all_figures));
	iterator = iterator->next;
	iterator->type = 'o';
	iterator->current = new;
	iterator->next = NULL;
}


