//
// Created by Demeter Xhoan on 3/22/21.
//

#include "parser.h"

void	set_light(char *string, t_all *scene)
{

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