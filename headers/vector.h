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

t_vector	get_new_vector(float x, float y, float z);
t_vector	vectors_subtraction(t_vector subtract_from, t_vector to_subtract);
float		vector_length(t_vector vector);
t_vector	vector_normalization(t_vector vector);
float		vectors_dot_product(t_vector first, t_vector second);
t_vector	vector_multiplying_by_number(t_vector vector, float number);

#endif //MINIRT_VECTOR_H
