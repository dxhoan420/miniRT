//
// Created by Demeter Xhoan on 2/24/21.
//

#include "../../hdrs/vector.h"
#include <math.h>

t_vec	create_vector(float x, float y, float z)
{
	t_vec	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

t_ray	create_ray(t_vec camera_coordinates, t_vec ray)
{
	t_ray	new_ray;

	new_ray.src = camera_coordinates;
	new_ray.dir = ray;
	return (new_ray);
}

float	vec_length(t_vec vec)
{
	return (sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

t_vec	vector_norm(t_vec vector)
{
	float	length;

	length = vec_length(vector);
	vector.x /= length;
	vector.y /= length;
	vector.z /= length;
	return (vector);
}
