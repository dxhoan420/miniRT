//
// Created by Demeter Xhoan on 3/22/21.
//

#include "parser.h"

void	parse_sphere(t_all *scene, char *string)
{
	t_vec	coordinates;
	float	diameter;
	t_rgb	rgb;

	string = set_vector(string, &coordinates, POINT);
	string = set_float(string, &diameter);
	set_rgb(string, &rgb);
	add_sphere(scene, coordinates, diameter, rgb);
}

void	parse_plane(t_all *scene, char *string)
{
	t_vec	coordinates;
	t_vec	normal;
	t_rgb	rgb;

	string = set_vector(string, &coordinates, POINT);
	string = set_vector(string, &normal, NORMAL);
	set_rgb(string, &rgb);
	add_plane(scene, coordinates, normal, rgb);
}

void	parse_triangle(t_all *scene, char *string)
{
	t_vec	first;
	t_vec	second;
	t_vec	third;
	t_rgb	rgb;

	string = set_vector(string, &first, POINT);
	string = set_vector(string, &second, POINT);
	string = set_vector(string, &third, POINT);
	set_rgb(string, &rgb);
	add_triangle(scene, first, create_ray(second, third), rgb);
}

void	parse_square(t_all *scene, char *string)
{
	t_vec	coordinates;
	t_vec	normal;
	float	size;
	t_rgb	rgb;

	string = set_vector(string, &coordinates, POINT);
	string = set_vector(string, &normal, NORMAL);
	string = set_float(string, &size);
	set_rgb(string, &rgb);
	add_square(scene, create_ray(coordinates, normal), size, rgb);
}

void	parse_cylinder(t_all *scene, char *string)
{
	t_vec	coordinates;
	t_vec	normal;
	float	diameter;
	float	height;
	t_rgb	rgb;

	string = set_vector(string, &coordinates, POINT);
	string = set_vector(string, &normal, NORMAL);
	string = set_float(string, &diameter);
	string = set_float(string, &height);
	set_rgb(string, &rgb);
	add_cylinder(scene, create_ray(coordinates, normal),
		create_vector (diameter, height, 421), rgb);
}
