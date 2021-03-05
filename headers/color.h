//
// Created by Demeter Xhoan on 3/5/21.
//

#ifndef MINIRT_COLOR_H
#define MINIRT_COLOR_H

typedef struct			s_color
{
	int r;
	int g;
	int	b;
}						t_color;

int		create_rgb(int r, int g, int b);
t_color	color_to_rgb(int color);
int 	rgb_to_color(t_color rgb);

#endif //MINIRT_COLOR_H
