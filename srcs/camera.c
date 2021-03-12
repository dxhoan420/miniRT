//
// Created by Demeter Xhoan on 2/20/21.
//

#include "../hdrs/miniRT.h"

void		add_camera(t_cameras **cameras, t_vector coordinates,
				 t_vector norma_vector,int field_of_view)
{
	t_cameras *iterator = *cameras;
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
		*cameras = new;
}

t_vector	cam_dir(t_vector origin, t_vector mz)
{
	t_vector mx;
	t_vector my;
	t_vector result_ray;

	mx = vecs_cross(create_vector(0, 1, 0), mz);
	my = vecs_cross(mz, mx);
	result_ray.x = origin.x * mx.x + origin.y * mx.y + origin.z * mx.z;
	result_ray.y = origin.x * my.x + origin.y * my.y + origin.z * my.z;
	result_ray.z = origin.x * mz.x + origin.y * mz.y + origin.z * mz.z;
	return (result_ray);
}

void		add_light(t_all *scene, t_vector coordinates, t_rgb rgb_norm)
{
	t_lights *iterator = scene->lights;
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
		scene->lights = new;
}