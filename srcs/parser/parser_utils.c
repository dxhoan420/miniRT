//
// Created by Demeter Xhoan on 4/20/21.
//

#include "parser.h"

int	is_start(char **string, char first, char second)
{
	char	*line;

	line = *string;
	if (*line++ == first)
	{
		if (second == '\0' && (*line == ' ' || *line == '\t'))
		{
			*string = line;
			return (1);
		}
		if (*line++ == second)
		{
			*string = line;
			return (1);
		}
	}
	return (0);
}

int	skip_space_comma(char **string)
{
	char	*line;

	line = *string;
	skip_space(&line);
	if (*line == ',')
	{
		line++;
		if (*line == '\0')
			error("Not enough information", *string);
		*string = line;
		return (1);
	}
	else
		error("Separation problem", *string);
	return (0);
}

int	skip_space(char **string)
{
	char	*line;

	line = *string;
	if (*line == ' ' || *line == '\t')
	{
		while (*line == ' ' || *line == '\t')
			line++;
		if (*line == '\0')
			error("Not enough information", *string);
		*string = line;
		return (1);
	}
	return (0);
}

void	parser_error(char *message, int number)
{
	printf("Error\n%s\nLINE: %i\n", message, number);
	exit(-1);
}
