//
// Created by Demeter Xhoan on 2/24/21.
//

#include <math.h>
#include "../../hdrs/vector.h"

t_vector	create_vector(float x, float y, float z)
{
	t_vector	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

t_ray	create_ray(t_vector camera_coordinates, t_vector ray)
{
	t_ray	new_ray;

	new_ray.src = camera_coordinates;
	new_ray.dir = ray;
	return (new_ray);
}

float	vec_length(t_vector vec)
{
	return (sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

t_vector	vector_norm(t_vector vector)
{
	float	length;

	length = vec_length(vector);
	vector.x /= length;
	vector.y /= length;
	vector.z /= length;
	return (vector);
}
