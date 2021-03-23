//
// Created by Demeter Xhoan on 3/22/21.
//

#include "parser.h"

void	set_sphere(char *string, t_all *scene)
{
	t_vec	coordinates;
	float	diameter;
	t_rgb	rgb;

	string = set_vector(string, &coordinates, POINT);
	string = set_float(string, &diameter);
	string = set_rgb(string, &rgb, FIGURE);
	add_sphere(scene, coordinates, diameter, rgb);
}

void	set_plane(char *string, t_all *scene)
{
	t_vec	coordinates;
	t_vec	normal;
	t_rgb	rgb;

	string = set_vector(string, &coordinates, POINT);
	string = set_vector(string, &normal, NORMAL);
	string = set_rgb(string, &rgb, FIGURE);
	add_plane(scene, coordinates, normal, rgb);
}

void	set_triangle(char *string, t_all *scene)
{
	t_vec	first;
	t_vec	second;
	t_vec	third;
	t_rgb	rgb;

	string = set_vector(string, &first, POINT);
	string = set_vector(string, &second, POINT);
	string = set_vector(string, &third, POINT);
	string = set_rgb(string, &rgb, FIGURE);
	add_triangle(scene, first, create_ray(second, third), rgb);
}

void	set_square(char *string, t_all *scene)
{
	t_vec	coordinates;
	t_vec	normal;
	float	size;
	t_rgb	rgb;

	string = set_vector(string, &coordinates, POINT);
	string = set_vector(string, &normal, NORMAL);
	string = set_float(string, &size);
	string = set_rgb(string, &rgb, FIGURE);
	add_square(scene, create_ray(coordinates, normal), size, rgb);
}

void	set_cylinder(char *string, t_all *scene)
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
	string = set_rgb(string, &rgb, FIGURE);
	add_cylinder(scene, create_ray(coordinates, normal),
					create_vector (diameter, height, 421), rgb);
}

