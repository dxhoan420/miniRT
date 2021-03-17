//
// Created by Demeter Xhoan on 2/24/21.
//

#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}				t_vec;

typedef struct s_ray
{
	t_vec	src;
	t_vec	dir;
}				t_ray;

t_vec	vecs_subtraction(t_vec subtract_from, t_vec to_subtract);
t_vec	vecs_cross(t_vec first, t_vec second);
t_vec	vecs_add(t_vec add_here, t_vec add_this);
t_vec	vec_multi(t_vec vector, float number);
t_vec	create_vector(float x, float y, float z);
t_vec	vector_norm(t_vec vector);
float	vec_length(t_vec vec);
float	vecs_dot(t_vec first, t_vec second);
t_ray	create_ray(t_vec ray, t_vec camera_coordinates);

#endif