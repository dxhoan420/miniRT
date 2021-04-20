//
// Created by Demeter Xhoan on 4/11/21.
//

#include "parser.h"

char	*set_vector(char *string, t_vec *vector, t_vector_type type)
{
	char	*origin;
	float	x;
	float	y;
	float	z;

	origin = string;
	string = set_float(string, &x);
	skip_space_comma(&string);
	string = set_float(string, &y);
	skip_space_comma(&string);
	string = set_float(string, &z);
	*vector = create_vector(x, y, z);
	if (type == NORMAL)
	{
		if (x == y && y == z && z == 0)
			error("Normal can't have all zero", origin);
		if (x < -1 || x > 1)
			error("X coordinate should be [-1, 1] for normal", origin);
		if (y < -1 || y > 1)
			error("Y coordinate should be [-1, 1] for normal", origin);
		if (z < -1 || z > 1)
			error("Z coordinate should be [-1, 1] for normal", origin);
	}
	skip_space(&string);
	return (string);
}

char	*set_rgb(char *string, t_rgb *rgb)
{
	char	*origin;

	origin = string;
	string = set_float(string, &rgb->r);
	if (rgb->r > 255)
		error("Red channel overflow", origin);
	if (rgb->r < 0)
		error("Red channel negative", origin);
	skip_space_comma(&string);
	string = set_float(string, &rgb->g);
	if (rgb->g > 255)
		error("Green channel overflow", origin);
	if (rgb->g < 0)
		error("Green channel negative", origin);
	skip_space_comma(&string);
	string = set_float(string, &rgb->b);
	if (rgb->b > 255)
		error("Blue channel overflow", origin);
	if (rgb->b < 0)
		error("Blue channel negative", origin);
	if (*string != '\0')
		error("Extra symbols after RGB", origin);
	return (string);
}

char 	*check_and_set_sign(char *str, float *positive)
{
	*positive = 1;
	while (((*str >= '\t' && *str <= '\r') || *str == ' ' || *str == ',')
		   && *str != '\0')
		str++;
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			*positive *= -1;
		str++;
	}
	return (str);
}

char	*set_float(char *str, float *result)
{
	float	power;
	float	positive;

	*result = 0;
	skip_space(&str);
	str = check_and_set_sign(str, &positive);
	while ((*str >= '0' && *str <= '9') && *str != '\0')
		*result = *result * 10 + (float)(*str++ - '0');
	if (*str != '.')
	{
		*result *= positive;
		return (str);
	}
	str++;
	power = 0;
	while ((*str >= '0' && *str <= '9') && *str != '\0')
	{
		power++;
		*result = *result * 10 + (float)(*str++ - '0');
	}
	if (power > 0)
		*result = *result / powf(10, power) * positive;
	return (str);
}
