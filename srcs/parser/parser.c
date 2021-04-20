//
// Created by Demeter Xhoan on 3/20/21.
//

#include "parser.h"

void	type_check(t_all *scene, char *line, t_count *checks)
{
	if (*line == '#' || *line == '\0')
		return ;
	if (is_start(&line, 'R', '\0'))
		parse_screen_resolution(scene, line, checks);
	else if (is_start(&line, 'A', '\0'))
		parse_ambient(scene, line, checks);
	else if (is_start(&line, 'c', '\0'))
		parse_camera(scene, line);
	else if (is_start(&line, 'l', '\0'))
		parse_light(scene, line);
	else if (is_start(&line, 's', 'p'))
		parse_sphere(scene, line);
	else if (is_start(&line, 'p', 'l'))
		parse_plane(scene, line);
	else if (is_start(&line, 's', 'q'))
		parse_square(scene, line);
	else if (is_start(&line, 'c', 'y'))
		parse_cylinder(scene, line);
	else if (is_start(&line, 't', 'r'))
		parse_triangle(scene, line);
	else
		error("Can't handle. Undefined identifier.", line);
}

void	parser (t_all *scene)
{
	int		fd;
	int		have_new_line;
	char	*line;
	t_count	checks;

	checks.letter_a = '\0';
	checks.letter_r = '\0';
	checks.line_counter = 1;
	fd = open(scene->filename, O_RDONLY);
	if (fd == -1)
		error("Can't open file for read", scene->filename);
	have_new_line = get_next_line(fd, &line);
	while (have_new_line)
	{
		type_check(scene, line, &checks);
		free(line);
		have_new_line = get_next_line(fd, &line);
		checks.line_counter++;
	}
	type_check(scene, line, &checks);
	free(line);
	if (checks.letter_a == '\0' || checks.letter_r == '\0')
		error("No lines starting with A or R", scene->filename);
	close(fd);
}
