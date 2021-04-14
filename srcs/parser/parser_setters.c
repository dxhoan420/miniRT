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
	string = set_float(string, &y);
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
	return (string);
}

char	*set_rgb(char *string, t_rgb *rgb, t_color_type type)
{
	char	*origin;
	float	ratio;

	origin = string;
	if (type == LIGHT)
	{
		string = set_float(string, &ratio);
		if (ratio > 1)
			error("Ratio error", origin);
	}
	string = set_float(string, &rgb->r);
	if (rgb->r > 255)
		error("Red channel overflow", origin);
	string = set_float(string, &rgb->g);
	if (rgb->g > 255)
		error("Green channel overflow", origin);
	string = set_float(string, &rgb->b);
	if (rgb->b > 255)
		error("Blue channel overflow", origin);
	if (type == LIGHT)
		*rgb = create_rgb_norm(rgb->r, rgb->g, rgb->r, ratio);
	return (string);
}

char 	*skip_and_set_sign(char *str, float *positive)
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

char	*check_origin_to_current(char *origin, char *current)
{
	if (origin == current)
		error("PARSER UNKNOWN ERROR", origin);
	return (current);
}

char	*set_float(char *str, float *result)
{
	char	*origin;
	float	power;
	float	positive;

	*result = 0;
	origin = str;
	str = skip_and_set_sign(str, &positive);
	while ((*str >= '0' && *str <= '9') && *str != '\0')
		*result = *result * 10 + (float)(*str++ - '0');
	if (*str != '.')
	{
		*result *= positive;
		return (check_origin_to_current(origin, str));
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
	return (check_origin_to_current(origin, str));
}
