//
// Created by Demeter Xhoan on 2/20/21.
//

#include "miniRT.h"

float	distance_to_sphere(t_ray ray, struct s_figure *sphere)
{
	t_vec		cam_to_center;
	t_vec		nums;
	float		discriminant;
	float		distance;

	cam_to_center = vecs_subtraction(ray.src, sphere->first);
	nums.x = vecs_dot(ray.dir, ray.dir);
	nums.y = 2 * (vecs_dot(cam_to_center, ray.dir));
	nums.z = vecs_dot(cam_to_center, cam_to_center)
		- (sphere->radius_or_size * sphere->radius_or_size);
	discriminant = nums.y * nums.y - 4 * nums.z * nums.x;
	if (discriminant < 0)
		return (0);
	distance = (-nums.y - sqrtf(discriminant)) / (2 * nums.x);
	if (distance < 0)
	{
		distance = (-nums.y + sqrtf(discriminant)) / (2 * nums.x);
		sphere->side = INNER;
	}
	else
		sphere->side = OUTER;
	return (distance);
}

void	add_sphere(t_all *scene, t_vec center, float diameter, t_rgb rgb)
{
	struct s_figure	*sphere;

	sphere = get_last_figure_of_scene(scene, rgb);
	sphere->type = SPHERE;
	sphere->get_distance = distance_to_sphere;
	sphere->first = center;
	sphere->radius_or_size = diameter / 2;
}
