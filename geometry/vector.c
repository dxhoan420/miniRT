//
// Created by Demeter Xhoan on 2/24/21.
//

#include "../headers/miniRT.h"

t_vector	new_vector(float x, float y, float z)
{
	t_vector	vector;

	//if (!(vector = malloc(sizeof(t_vector))))
	//	exit(-1);
	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

/*
** Maybe should not use pointer of vector?
** and return the value...
*/

t_vector	subtraction_of_vectors(t_vector minuend, t_vector subtrahend)
{
	t_vector	difference;

	difference = new_vector(minuend.x - subtrahend.x,
						 minuend.y - subtrahend.y,
						 minuend.z - subtrahend.z);
	return (difference);
}

float		length_of_vector(t_vector vector)
{
	float	length;

	length = sqrt(vector.x * vector.x +
			vector.y * vector.y +
			vector.z * vector.z);
	return (length);
}

t_vector	normalization_of_vector(t_vector vector)
{
	float	length;

	length = length_of_vector(vector);
	vector.x /= length;
	vector.y /= length;
	vector.z /= length;
	return (vector);
}

float		multiplication_of_vectors(t_vector first, t_vector second)
{
	float	dot_product;

	dot_product = first.x * second.x +
			first.y * second.y +
			first.z * second.z;
	return (dot_product);
}
