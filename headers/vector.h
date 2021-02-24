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
t_vector	subtraction_of_vectors(t_vector minuend, t_vector subtrahend);
float		length_of_vector(t_vector vector);
t_vector	normalization_of_vector(t_vector vector);
float		multiplication_of_vectors(t_vector first, t_vector second);

#endif //MINIRT_VECTOR_H
