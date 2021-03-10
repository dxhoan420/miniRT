//
// Created by Demeter Xhoan on 3/10/21.
//

#include "../headers/miniRT.h"

void	add_plane(t_all *scene, t_vector coordinates, t_vector norm, t_rgb rgb)
{
	t_figures *iterator = scene->figures;
	struct s_figure *new;

	new = malloc(sizeof (struct s_figure));
	if (new == NULL)
		exit(-1);
	new->id	= PLANE;
	new->first_or_center = coordinates;
	new->second_or_norma = norm;
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