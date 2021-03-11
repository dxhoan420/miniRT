//
// Created by Demeter Xhoan on 2/24/21.
//

#ifndef MINIRT_VECTOR_H
#define MINIRT_VECTOR_H

typedef struct 	s_vector
{
	float x;
	float y;
	float z;
}				t_vector;

typedef struct	s_ray
{
	t_vector src;
	t_vector dir;
}				t_ray;

t_vector	vecs_subtraction(t_vector subtract_from, t_vector to_subtract);
t_vector	vec_multiply_by_number(t_vector vector, float number);
t_vector	vecs_addition(t_vector add_here, t_vector add_this);
t_vector	create_vector(float x, float y, float z);
t_vector	vector_norm(t_vector vector);
float		vec_length(t_vector vector);
float		vecs_dot_product(t_vector first, t_vector second);
t_ray 		create_ray(t_vector ray, t_vector camera_coordinates);

#endif //MINIRT_VECTOR_H