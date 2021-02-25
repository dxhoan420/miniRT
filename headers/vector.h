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

t_vector	new_vector(float x, float y, float z);
t_vector	subtraction_vectors(t_vector subtract_from, t_vector to_subtract);
float		length_of_vector(t_vector vector);
t_vector	normalization_of_vector(t_vector vector);
float		dot_product_of_vectors(t_vector first, t_vector second);
t_vector	multiply_vector_by_number(t_vector vector, float number);

#endif //MINIRT_VECTOR_H
