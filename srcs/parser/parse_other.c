//
// Created by Demeter Xhoan on 3/22/21.
//

#include "parser.h"

void	parse_light(t_all *scene, char *string)
{
	t_vec	coordinates;
	t_rgb	rgb;
	float	ratio;
	char	*origin;

	origin = string;

	string = set_vector(string, &coordinates, POINT);
	string = set_float(string, &ratio);
	if (ratio > 1)
		error("Ratio error", origin);
	set_rgb(string, &rgb);
	rgb = create_rgb_norm(rgb.r, rgb.g, rgb.b, ratio);
	add_light(scene, coordinates, rgb);
}

void	parse_camera(t_all *scene, char *string)
{
	char	*origin;
	t_vec	coordinates;
	t_vec	normal;
	float	fov;

	origin = string;
	string = set_vector(string, &coordinates, POINT);
	string = set_vector(string, &normal, NORMAL);
	string = set_float(string, &fov);
	if (*string != '\0')
		error("Extra symbols after FOV", origin);
	if (fov < 1)
		error("Can't render for fov < 1", origin);
	if (fov > 180)
		error("MAX FOV = 180", origin);
	if (normal.x == 0 && normal.z == 0)
		error("Can't compute picture with such camera orientation", origin);
	add_camera(scene, coordinates, normal, fov);
}

void	parse_screen_resolution(t_all *scene, char *string, t_count *checks)
{
	float	temp;
	char	*origin;

	if (checks->letter_r == 'R')
		error("Lines starting with R must appear once", string);
	else
		checks->letter_r = 'R';
	origin = string;
	string = set_float(string, &temp);
	scene->x_res = (int)temp;
	skip_space(&string);
	string = set_float(string, &temp);
	scene->y_res = (int)temp;
	if (*string != '\0')
		error("Extra symbols after RESOLUTION", origin);
	if (scene->x_res <= 0 || scene->y_res <= 0)
		error("Negative resolution: need positive integer", origin);
	if (scene->x_res > 16384 || scene->y_res > 16384)
		error("Maximum allowed size is 16384", origin);
}

void	parse_ambient(t_all *scene, char *string, t_count *checks)
{
	t_rgb	rgb;
	float	ratio;
	char	*origin;

	if (checks->letter_a == 'A')
		error("Lines starting with A must appear once", string);
	else
		checks->letter_a = 'A';
	origin = string;
	string = set_float(string, &ratio);
	if (ratio > 1)
		error("Ratio error", origin);
	skip_space(&string);
	string = set_rgb(string, &rgb);
	scene->ambient_rgb_norm = create_rgb_norm(rgb.r, rgb.g, rgb.b, ratio);
}