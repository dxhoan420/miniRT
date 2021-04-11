//
// Created by Demeter Xhoan on 3/22/21.
//

#include "parser.h"

void	set_light(char *string, t_all *scene)
{
	t_vec	coordinates;
	t_rgb	rgb_norm;

	string = set_vector(string, &coordinates, POINT);
	string = set_rgb(string, &rgb_norm, LIGHT);
	add_light(scene, coordinates, rgb_norm);
}

void	set_camera(char *string, t_all *scene)
{
	char	*origin;
	t_vec	coordinates;
	t_vec	normal;
	float	fov;

	origin = string;
	string = set_vector(string, &coordinates, POINT);
	string = set_vector(string, &normal, NORMAL);
	string = set_float(string, &fov);
	if (fov < 1)
		error("Can't render for fov < 1", origin);
	if (fov > 180)
		error("MAX FOV = 180", origin);
	if (normal.x == 0 && normal.z == 0)
		error("Can't compute picture with such camera orientation", origin);
	add_camera(scene, coordinates, normal, fov);
}

void	set_other(char *string, t_all *scene)
{
	if (*string == 'l')
	{
		if ((*(string + 1) >= '\t' && *(string + 1) <= '\r')
			|| *(string + 1) == ' ')
			return (set_light(string + 1, scene));
	}
	if (*string == 's')
	{
		if (*(string + 1) == 'p')
			return (set_sphere(string + 2, scene));
		if (*(string + 1) == 'q')
			return (set_square(string + 2, scene));
	}
	if (*string == 'p')
		if (*(string + 1) == 'l')
			return (set_plane(string + 2, scene));
	if (*string == 't')
		if (*(string + 1) == 'r')
			return (set_triangle(string + 2, scene));
	if (*string == 'c')
		if (*(string + 1) == 'y')
			return (set_cylinder(string + 2, scene));
	error("Can't handle this shit", string);
}

