//
// Created by Demeter Xhoan on 2/20/21.
//

#include "../hdrs/miniRT.h"

void	add_camera(t_cameras **cams, t_vec point,
				   t_vec normal, int fov)
{
	t_cameras	*iterator;
	t_cameras	*new;

	iterator = *cams;
	new = malloc(sizeof (t_cameras));
	if (new == NULL)
		exit(-1);
	new->coordinates = point;
	new->norma_vector = normal;
	new->field_of_view = fov;
	new->next = NULL;
	if (iterator != NULL)
	{
		while (iterator->next != NULL)
			iterator = iterator->next;
		iterator->next = new;
	}
	else
		*cams = new;
}

t_vec	cam_dir(t_vec origin, t_vec mz)
{
	t_vec	mx;
	t_vec	my;
	t_vec	result_ray;

	mx = vecs_cross(create_vector(0, 1, 0), mz);
	my = vecs_cross(mz, mx);
	result_ray.x = origin.x * mx.x + origin.y * mx.y + origin.z * mx.z;
	result_ray.y = origin.x * my.x + origin.y * my.y + origin.z * my.z;
	result_ray.z = origin.x * mz.x + origin.y * mz.y + origin.z * mz.z;
	return (result_ray);
}

void	add_light(t_all *scene, t_vec coordinates, t_rgb rgb_norm)
{
	t_lights		*iterator;
	struct s_light	*new;

	iterator = scene->lights;
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
