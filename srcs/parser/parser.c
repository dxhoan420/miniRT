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
	scene->x_res = (int)temp;
	string = set_float(string, &temp);
	scene->y_res = (int)temp;
	if (scene->x_res <= 0 || scene->y_res <= 0)
		error("Negative resolution: need positive number", origin);
	if (scene->x_res > 16384 || scene->y_res > 16384)
		error("Maximum allowed size is 16384", origin);
}

char	*set_rgb(char *string, t_rgb *rgb, t_color_type type)
{
	char	*origin;
	float	ratio;
	float	r;
	float	g;
	float	b;

	origin = string;
	if (type == LIGHT)
	{
		string = set_float(string, &ratio);
		if (ratio > 1)
			error("Ratio error", origin);
	}
	string = set_float(string, &r);
	if (r > 255)
		error("Red channel overflow", origin);
	string = set_float(string, &g);
	if (g > 255)
		error("Green channel overflow", origin);
	string = set_float(string, &b);
	if (b > 255)
		error("Blue channel overflow", origin);
	if (type == LIGHT)
		*rgb = create_rgb_norm(r, g, b, ratio);
	else
		*rgb = create_rgb(r, g, b);
	return (string);
}

void	set_ambient(char *string, t_all *scene)
{
	t_rgb rgb_norm;

	string = set_rgb(string, &rgb_norm, LIGHT);
	scene->ambient_rgb_norm = rgb_norm;
}

void	type_check(t_all *scene, t_cameras **cameras, char *string,
						char *a_r_checks)
{
	printf("%s\n", string);

	if (*string == '#' || *string == '\0')
		return;
	if (*string == 'R')
	{
		if (a_r_checks[1] == *string)
			error("Lines starting with R must appear once", string);
		a_r_checks[1] = 'R';
		set_screen_resolution(string + 1, scene);
	}
	else if (*string == 'A')
	{
		if (a_r_checks[0] == *string)
			error("Lines starting with A must appear once", string);
		a_r_checks[0] = 'A';
 		set_ambient(string + 1, scene);
	}
	else if (*string == 'c' && ((*(string + 1) >= '\t' && *(string + 1) <= '\r')
								|| *(string + 1) == ' '))
	{
			set_camera(string + 1, cameras);
	}
	else
		set_other(string, scene);
}

void	parser (t_all *scene, t_cameras **cameras, char *filename)
{
	int fd;
	int have_found_new_line;
	char *string;
	char a_r_checks[3];

	//need to check filename for .rt
	a_r_checks[0] = '2';
	a_r_checks[1] = '1';
	a_r_checks[2] = '\0';
	fd = open(filename, O_RDONLY);
	if (fd  == -1)
		error("Can't open file for read", filename);
	have_found_new_line = get_next_line(fd, &string);
	while (have_found_new_line)
	{
		type_check(scene, cameras, string, a_r_checks);
		free(string);
		have_found_new_line = get_next_line(fd, &string);
	}
	type_check(scene, cameras, string, a_r_checks);
	free(string);
	if (a_r_checks[1] == '2' || a_r_checks[2] == '1')
		error("No lines starting with A or R", filename);
	close(fd);
}
