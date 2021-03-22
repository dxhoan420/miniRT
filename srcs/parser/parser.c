//
// Created by Demeter Xhoan on 3/20/21.
//

#include "parser.h"

void	set_screen_resolution(char *string, t_all *scene)
{
	float	temp;
	char	*origin;

	origin = string;
	string = set_float(string, &temp);
	scene->x_resolution = (int)temp;
	string = set_float(string, &temp);
	scene->y_resolution = (int)temp;
	if (scene->x_resolution <= 0 || scene->y_resolution <= 0)
		error("Negative resolution: need positive number", origin);
}

void	set_ambient(char *string, t_all *scene)
{
	char	*origin;
	float	ratio;
	float	r;
	float	g;
	float	b;

	origin = string;
	string = set_float(string, &ratio);
	if (ratio > 1)
		error("Ratio error", origin);
	string = set_float(string, &r);
	if (r > 255)
		error("Red channel overflow", origin);
	string = set_float(string, &g);
	if (g > 255)
		error("Green channel overflow", origin);
	string = set_float(string, &b);
	if (b > 255)
		error("Blue channel overflow", origin);
	scene->ambient_rgb_norm = create_rgb_norm(r, g, b, ratio);
}

void	set_camera(char *string, t_cameras **cameras)
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
	add_camera(cameras, coordinates, normal, fov);
}

char	type_check(t_all *scene, t_cameras **cameras, char *string)
{
	char	type;

	printf("%s\n", string);

	if (*string == 'R')
	{
		set_screen_resolution(++string, scene);
		return ('R');
	}
	else if (*string == 'A')
	{
		set_ambient(++string, scene);
		return ('A');
	}
	else if (*string == 'c')
	{
		if ((*(string + 1) >= '\t' && *(string + 1) <= '\r')
				|| *(string + 1) == ' ')
			set_camera(++string, cameras);
	}
	else
		set_other(string, scene);
	return (*string);
}

void	parser (t_all *scene, t_cameras **cameras, char *filename)
{
	int fd;
	int have_found_new_line;
	char *string;
	char a_r_checks[3];

	a_r_checks[1] = '2';
	a_r_checks[2] = '1';
	fd = open(filename, O_RDONLY);
	if (fd  == -1)
		error("Can't open file for read", filename);
	have_found_new_line = get_next_line(fd, &string);
	while (have_found_new_line)
	{
		a_r_checks[0] = type_check(scene, cameras, string);
		if (a_r_checks[0] == a_r_checks[1] || a_r_checks[0] == a_r_checks[2])
			error("Lines starting with A or R must appear once", string);
		if (a_r_checks[0] == 'A')
			a_r_checks[1] = 'A';
		if (a_r_checks[0] == 'R')
			a_r_checks[2] = 'R';
		have_found_new_line = get_next_line(fd, &string);
	}
	if (a_r_checks[1] == '2' || a_r_checks[2] == '1')
		error("No lines starting with A or R", filename);
	close(fd);
}
