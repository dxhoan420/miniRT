//
// Created by Demeter Xhoan on 2/24/21.
//

#include "../headers/miniRT.h"

t_vector	get_new_vector(float x, float y, float z)
{
	t_vector	vector;
	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

/*
** Maybe should not use pointer of vector?
** and return the value...
*/

t_vector	vectors_subtraction(t_vector subtract_from, t_vector to_subtract)
{
	subtract_from.x -= to_subtract.x;
	subtract_from.y -= to_subtract.y;
	subtract_from.z -= to_subtract.z;
	return (subtract_from);
}

float		vector_length(t_vector vector)
{
	return (sqrtf(vector.x * vector.x +
				  vector.y * vector.y +
				  vector.z * vector.z	));
}

t_vector	vector_normalization(t_vector vector)
{
	float	length;

	length = vector_length(vector);
	vector.x /= length;
	vector.y /= length;
	vector.z /= length;
	return (vector);
}

float		vectors_dot_product(t_vector first, t_vector second)
{
	float	result;

	result = first.x * second.x +
			first.y * second.y +
			first.z * second.z;
	return (result);
}

t_vector	vector_multiplying_by_number(t_vector vector, float number)
{
	vector.x *= number;
	vector.y *= number;
	vector.z *= number;
	return (vector);
}