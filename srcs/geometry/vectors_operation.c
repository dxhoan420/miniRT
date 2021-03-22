//
// Created by Demeter Xhoan on 3/17/21.
//

#include "vector.h"

t_vec	vecs_subtraction(t_vec subtract_from, t_vec to_subtract)
{
	subtract_from.x -= to_subtract.x;
	subtract_from.y -= to_subtract.y;
	subtract_from.z -= to_subtract.z;
	return (subtract_from);
}

float	vecs_dot(t_vec first, t_vec second)
{
	float	result;

	result = first.x * second.x + first.y * second.y + first.z * second.z;
	return (result);
}

t_vec	vecs_cross(t_vec first, t_vec second)
{
	t_vec	product;

	product.x = first.y * second.z - first.z * second.y;
	product.y = first.z * second.x - first.x * second.z;
	product.z = first.x * second.y - first.y * second.x;
	return (product);
}

t_vec	vec_multi(t_vec vector, float number)
{
	vector.x *= number;
	vector.y *= number;
	vector.z *= number;
	return (vector);
}

t_vec	vecs_add(t_vec add_here, t_vec add_this)
{
	add_here.x += add_this.x;
	add_here.y += add_this.y;
	add_here.z += add_this.z;
	return (add_here);
}
