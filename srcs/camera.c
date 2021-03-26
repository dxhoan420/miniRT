//
// Created by Demeter Xhoan on 2/20/21.
//

#include "miniRT.h"

void	add_camera(t_cameras **cams, t_vec point,
				   t_vec normal, float fov)
{
	t_cameras	*iterator;
	t_cameras	*new;

	iterator = *cams;
	new = malloc(sizeof (t_cameras));
	if (new == NULL)
		exit(-666);
	new->coordinates = point;
	new->orient_vector = vector_norm(normal);
	new->fov = fov;
	if (iterator != NULL)
	{
		while (iterator->next != NULL && iterator->next != *cams)
			iterator = iterator->next;
		iterator->next = new;
		new->next = *cams;
	}
	else
	{
		*cams = new;
		new->next = NULL;
	}
}

void	add_light(t_all *scene, t_vec coordinates, t_rgb rgb_norm)
{
	t_lights		*iterator;
	struct s_light	*new;

	iterator = scene->lights;
	new = malloc(sizeof(struct s_light));
	if (new == NULL)
		exit(-666);
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
		scene->lights = new;
}
