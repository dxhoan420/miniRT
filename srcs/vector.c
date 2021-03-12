//
// Created by Demeter Xhoan on 2/24/21.
//

#include "../hdrs/miniRT.h"

t_vector	create_vector(float x, float y, float z)
{
	t_vector	vector;
	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

t_ray 		create_ray(t_vector ray, t_vector camera_coordinates)
{
	t_ray new_ray;

	new_ray.src = camera_coordinates;
	new_ray.dir = ray;
	return (new_ray);
}

t_vector	vecs_subtraction(t_vector subtract_from, t_vector to_subtract)
{
	subtract_from.x -= to_subtract.x;
	subtract_from.y -= to_subtract.y;
	subtract_from.z -= to_subtract.z;
	return (subtract_from);
}

float		vec_length(t_vector vector)
{
	return (sqrtf(vector.x * vector.x +
				  vector.y * vector.y +
				  vector.z * vector.z	));
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

float		vecs_dot(t_vector first, t_vector second)
{
	float	result;

	result = first.x * second.x +
			first.y * second.y +
			first.z * second.z;
	return (result);
}

t_vector	vecs_cross(t_vector first, t_vector second)
{
	t_vector product;

	product.x = first.y * second.z - first.z * second.y;
	product.y = first.z * second.x - first.x * second.z;
	product.z = first.x * second.y - first.y * second.x;
	return (product);
}

t_vector	vec_multi(t_vector vector, float number)
{
	vector.x *= number;
	vector.y *= number;
	vector.z *= number;
	return (vector);
}

t_vector	vecs_add(t_vector add_here, t_vector add_this)
{
	add_here.x += add_this.x;
	add_here.y += add_this.y;
	add_here.z += add_this.z;
	return (add_here);
}