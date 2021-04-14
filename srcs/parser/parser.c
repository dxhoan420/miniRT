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

void	set_ambient(char *string, t_all *scene)
{
	t_rgb	rgb_norm;

	string = set_rgb(string, &rgb_norm, LIGHT);
	scene->ambient_rgb_norm = rgb_norm;
}

void	type_check(t_all *scene, char *string, char *a_r_checks)
{
	if (*string == '#' || *string == '\0')
		return ;
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
		set_camera(string + 1, scene);
	else
		set_other(string, scene);
}

void	parser (t_all *scene, char *rt_filename)
{
	int		fd;
	int		have_found_new_line;
	char	*string;
	char	a_r_checks[3];

	a_r_checks[0] = '2';
	a_r_checks[1] = '1';
	a_r_checks[2] = '\0';
	fd = open(rt_filename, O_RDONLY);
	if (fd == -1)
		error("Can't open file for read", rt_filename);
	have_found_new_line = get_next_line(fd, &string);
	while (have_found_new_line)
	{
		type_check(scene, string, a_r_checks);
		free(string);
		have_found_new_line = get_next_line(fd, &string);
	}
	type_check(scene, string, a_r_checks);
	free(string);
	if (a_r_checks[1] == '2' || a_r_checks[2] == '1')
		error("No lines starting with A or R", rt_filename);
	close(fd);
}
